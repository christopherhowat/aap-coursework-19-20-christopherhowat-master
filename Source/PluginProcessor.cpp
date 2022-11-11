/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
SpectralDistortionAudioProcessor::SpectralDistortionAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
    : AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
        .withInput("Input", AudioChannelSet::stereo(), true)
#endif
        .withOutput("Output", AudioChannelSet::stereo(), true)
#endif
    ), treeState(*this, nullptr, Identifier("PARAMETERS"),
        { std::make_unique<AudioParameterFloat>("lowVolume", "LowVolume", 0.0f, 2.f, 1.0f),
        std::make_unique<AudioParameterFloat>("highVolume", "HighVolume", 0.0f, 2.f, 1.0f),

        std::make_unique<AudioParameterFloat>("drive", "Drive", 0.f, 20.f, 0.f),
        std::make_unique<AudioParameterInt>("cutoff", "Cutoff", 20.f, 3000.f, 20),
        std::make_unique<AudioParameterFloat>("blend", "Blend", 0.f, 1.f, 0.f),
        std::make_unique<AudioParameterFloat>("gain", "Gain", 0.f, 1.f, 0.f) })

#endif
{
    const StringArray params = { "highVolume", "lowVolume", "drive", "cutoff", "blend", "gain" };
    for (int i = 0; i <= 3; ++i)
    {

        treeState.addParameterListener(params[i], this);
    }
}


    SpectralDistortionAudioProcessor::~SpectralDistortionAudioProcessor()
    {}


//==============================================================================
const String SpectralDistortionAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool SpectralDistortionAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool SpectralDistortionAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool SpectralDistortionAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double SpectralDistortionAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int SpectralDistortionAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int SpectralDistortionAudioProcessor::getCurrentProgram()
{
    return 0;
}

void SpectralDistortionAudioProcessor::setCurrentProgram (int index)
{
}

const String SpectralDistortionAudioProcessor::getProgramName (int index)
{
    return {};
}

void SpectralDistortionAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void SpectralDistortionAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..


    // Set size of temporary buffers
    LPBuffer.setSize(2, samplesPerBlock);
    HPBuffer.setSize(2, samplesPerBlock);

    // Clear buffers
    LPBuffer.clear();
    HPBuffer.clear();

}

void SpectralDistortionAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool SpectralDistortionAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
return true;
#else
// This is the place where you check if the layout is supported.
// In this template code we only support mono or stereo.
if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
    && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
    return false;

// This checks if the input layout matches the output layout
#if ! JucePlugin_IsSynth
if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
return false;
#endif

return true;
#endif
}
#endif
//AudioProcessorValueTreeState& SpectralDistortionAudioProcessor::getState() {
//    return *treeState;
//}


void SpectralDistortionAudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();



    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear(i, 0, buffer.getNumSamples());



    

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        int cutoff = *treeState. getRawParameterValue("cutoff");

        float sampleRate = getSampleRate();

        LPCoefficients = IIRCoefficients::makeLowPass(sampleRate, cutoff); // Call makeLowPass to generate a set of coefficients for the IIR filter
        LPFilter1[0].setCoefficients(LPCoefficients);
        LPFilter2[0].setCoefficients(LPCoefficients);
        LPFilter1[1].setCoefficients(LPCoefficients);
        LPFilter2[1].setCoefficients(LPCoefficients);

        HPCoefficients = IIRCoefficients::makeHighPass(sampleRate, cutoff); // Call makeHighPass to generate a set of coefficients for the IIR filter
        HPFilter1[0].setCoefficients(HPCoefficients);
        HPFilter2[1].setCoefficients(HPCoefficients);
        HPFilter1[0].setCoefficients(HPCoefficients);
        HPFilter2[1].setCoefficients(HPCoefficients);

        LPBuffer.copyFrom(channel, 0, buffer, channel, 0, buffer.getNumSamples());
        HPBuffer.copyFrom(channel, 0, buffer, channel, 0, buffer.getNumSamples());


        // Apply filter to samples in temp buffers (2 x butter low pass filter is equivelent to Linkwitz-Riley Filter
        // which are ideal for crossover filters due to their flat passband

        LPFilter1[channel].processSamples(LPBuffer.getWritePointer(channel), LPBuffer.getNumSamples());
        LPFilter2[channel].processSamples(LPBuffer.getWritePointer(channel), LPBuffer.getNumSamples());
        HPFilter1[channel].processSamples(HPBuffer.getWritePointer(channel), HPBuffer.getNumSamples());
        HPFilter2[channel].processSamples(HPBuffer.getWritePointer(channel), HPBuffer.getNumSamples());

        // Here could be were you would put your processing code for each band

        // Multipy high pass by –1 so that the branches of your crossover pair are in-phase


        for (int i = 0; i < buffer.getNumSamples(); ++i)
        {//declaring variables
            float drive = *treeState .getRawParameterValue("drive");
            float blend = *treeState .getRawParameterValue("blend");
            float gain = *treeState .getRawParameterValue("gain");
            

            float LPchannelData = LPBuffer .getSample(channel, i);
            float HPchannelData = HPBuffer .getSample(channel, i);
            float amount = drive * 10;
            float HPClean = HPchannelData;
            float LPClean = LPchannelData;


             





            if (menuChoice == 1) // soft clip algo
            {


                if (HPchannelData > 0 && HPchannelData <= 1)
                {
                    HPchannelData = ((1 + amount) * HPchannelData) / (1 + amount * HPchannelData);

                }
                else if (HPchannelData <= 0 && HPchannelData >= -1)
                {
                    HPchannelData = ((1 + amount) * HPchannelData) / (1 - amount * HPchannelData);

                }

                HPchannelData = ((HPchannelData * blend) + (HPClean * 1 - blend)) / 2 * gain;




                if (LPchannelData > 0 && LPchannelData <= 1)
                {
                    LPchannelData = ((1 + amount) * LPchannelData) / (1 + amount * LPchannelData);
                }

                
                else if (LPchannelData <= 0 && LPchannelData >= -1)
                {
                    LPchannelData = ((1 + amount) * LPchannelData) / (1 - amount * LPchannelData);
                    
                }

                LPchannelData = ((LPchannelData * blend) + (LPClean * 1 - blend)) / 2 * gain;

            }



            else if (menuChoice == 2) // soft clip 2 algo

            {
                amount = amount / 2;

                if (HPchannelData > 0 && HPchannelData <= 1)
                {
                    HPchannelData = 1 - (pow(((1 - HPchannelData)), amount));

                }
                else if (HPchannelData <= 0 && HPchannelData >= -1)
                {
                    HPchannelData = - 1 + (pow(((1 + HPchannelData)), amount));

                }

                HPchannelData = ((HPchannelData * blend) + (HPClean * 1 - blend)) / 2 * gain;




                if (LPchannelData > 0 && LPchannelData <= 1)
                {
                    LPchannelData = 1 - (pow(((1 - LPchannelData)), amount));
                }


                else if (LPchannelData <= 0 && LPchannelData >= -1)
                {
                    LPchannelData = -1 + (pow(((1 + LPchannelData)), amount));

                }

                LPchannelData = ((LPchannelData * blend) + (LPClean * 1 - blend)) / 2 * gain;

            }
            else if (menuChoice == 3) //overdrive algo

            {


                if (HPchannelData >= 0 && HPchannelData <= 1/3)
                {
                    HPchannelData = HPchannelData * 2;
                }

                else if (HPchannelData >= 1 / 3 && HPchannelData <= 2/3)
                {
                    HPchannelData =  (pow( 3 - ( 2 - ( 3 * HPchannelData ) ), 2.0) / (3));
                }
                
                else if (HPchannelData >= 2 / 3 && HPchannelData <= 1)
                {
                    HPchannelData = 1;

                }
                HPchannelData = ((HPchannelData * blend) + (HPClean * 1 - blend)) / 2 * gain;


                if (LPchannelData >= 0 && LPchannelData <= 1 / 3)
                {
                    LPchannelData = LPchannelData * 2;
                }

                else if (LPchannelData >= 1 / 3 && LPchannelData <= 2 / 3)
                {
                    LPchannelData = (pow(3 - (2 - (3 * LPchannelData)), 2.0) / (3));
                }

                else if (LPchannelData >= 2 / 3 && LPchannelData <= 1)
                {
                    LPchannelData = 1;

                }
                LPchannelData = ((LPchannelData * blend) + (LPClean * 1 - blend)) / 2 * gain;

                LPchannelData = LPchannelData * 0.1;
               
            }

        // set sample to distorted sample
            HPBuffer.setSample(channel, i, HPchannelData);
            LPBuffer.setSample(channel, i, LPchannelData);
            
            
        



 


           


            
        


        }

        
        float lowvolume = *treeState.getRawParameterValue("lowVolume");
        float highvolume = *treeState.getRawParameterValue("highVolume");

        HPBuffer.applyGain(channel, 0, HPBuffer.getNumSamples(), -1.f);




        //changes eq volume
        LPBuffer.applyGain(channel, 0, LPBuffer.getNumSamples(), lowvolume);
        HPBuffer.applyGain(channel, 0, HPBuffer.getNumSamples(), highvolume);

        HPBuffer.addFrom(channel, 0, LPBuffer, channel, 0, LPBuffer.getNumSamples()); // Mix low pass and high pass samples together

        buffer.copyFrom(channel, 0, HPBuffer, channel, 0, HPBuffer.getNumSamples()); // Copy mixed samples to output buffer


        // ..do something to the data...
    }
}


        
    


//==============================================================================
bool SpectralDistortionAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* SpectralDistortionAudioProcessor::createEditor()
{
    return new SpectralDistortionAudioProcessorEditor (*this, treeState);
}

//==============================================================================
void SpectralDistortionAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

    auto state = treeState.copyState();
    std::unique_ptr<XmlElement> xml(state.createXml());
    copyXmlToBinary(*xml, destData);

    MemoryOutputStream stream(destData, true);
    stream.writeInt(menuChoice);


}

void SpectralDistortionAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

    std::unique_ptr<XmlElement> xmlState(getXmlFromBinary(data, sizeInBytes));

    if (xmlState.get() != nullptr)
        if (xmlState->hasTagName(treeState.state.getType()))
            treeState.replaceState(ValueTree::fromXml(*xmlState));

        MemoryInputStream stream(data, static_cast<size_t> (sizeInBytes), false);
        menuChoice = stream.readInt();



    }


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new SpectralDistortionAudioProcessor();
}
void SpectralDistortionAudioProcessor::parameterChanged(const String& paramterID, float newValue)
{}