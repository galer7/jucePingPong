/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/
class PingPong2AudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    PingPong2AudioProcessor();
    ~PingPong2AudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
	int getNumParameters();
	float getParameter(int index);
	void setParameter(int index, float newValue);
	const String getParameterName(int index);
	const String getParameterText(int index);
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

	void fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float * bufferData, const float * delayBufferData);

	void getFromDelayBuffer(AudioBuffer<float>, int channel, const int bufferLength, const int delayBufferLength, const float * bufferData, const float * delayBufferData);

	void feedbackDelay(int channel, const int bufferLength, const int delayBufferLength, const float * bufferData, const float * delayBufferData, float * dryBuffer);

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

	enum Parameters { gain = 0, totalNumParam };
	bool NeedsUIUpdate() { return UIUpdateFlag; };
	void RequestUIUpdate() { UIUpdateFlag = true; };
	void ClearUIUpdateFlag() { UIUpdateFlag = false; };

private:

	AudioBuffer<float> myDelayBuffer;
	int mWritePosition = 0;
	int mSampleRate = 44100; 
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PingPong2AudioProcessor)
	float UserParams[totalNumParam];
	bool UIUpdateFlag; //Valoare booleana pentru reimprospatarea interfetei grafice
};
