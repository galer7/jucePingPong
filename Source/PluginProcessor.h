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
    void fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void getFromDelayBuffer(AudioBuffer<float> buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData);
    void feedbackDelay(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData, float* dryBuffer);
    AudioBuffer<float> mDelayBuffer;

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

	bool NeedsUIUpdate() { return UIUpdateFlag; };
	void RequestUIUpdate() { UIUpdateFlag = true; };
	void ClearUIUpdateFlag() { UIUpdateFlag = false; };

	int lastUIWidth, lastUIHeight;

	enum Parameters
	{
		gainParam = 0,
		delayLengthParam,
		dryMixParam,
		wetMixParam,
		feedbackParam,
		numParameters
	};

	float gain;
	float delayLength;
	float dryMix;
	float wetMix;
	float feedback;

private:
	// circular buffer variables
	AudioBuffer<float> myDelayBuffer;
    int mWritePosition = 0;
    int mSampleRate;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PingPong2AudioProcessor)
	bool UIUpdateFlag; //Valoare booleana pentru reimprospatarea interfetei grafice
};
