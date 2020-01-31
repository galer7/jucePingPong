/*
  ==============================================================================

	This file was auto-generated!

	It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include <iostream>
#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
PingPong2AudioProcessor::PingPong2AudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	)
#endif
{
	gain = 0.0f; // implicit castigul este 0
	UIUpdateFlag = true; // se cere update de la interfața grafică
}

PingPong2AudioProcessor::~PingPong2AudioProcessor()
{
}

//==============================================================================
const String PingPong2AudioProcessor::getName() const
{
	return JucePlugin_Name;
}

bool PingPong2AudioProcessor::acceptsMidi() const
{
#if JucePlugin_WantsMidiInput
	return true;
#else
	return false;
#endif
}

bool PingPong2AudioProcessor::producesMidi() const
{
#if JucePlugin_ProducesMidiOutput
	return true;
#else
	return false;
#endif
}

bool PingPong2AudioProcessor::isMidiEffect() const
{
#if JucePlugin_IsMidiEffect
	return true;
#else
	return false;
#endif
}

double PingPong2AudioProcessor::getTailLengthSeconds() const
{
	return 0.0;
}

int PingPong2AudioProcessor::getNumPrograms()
{
	return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
				// so this should be at least 1, even if you're not really implementing programs.
}

int PingPong2AudioProcessor::getCurrentProgram()
{
	return 0;
}

void PingPong2AudioProcessor::setCurrentProgram(int index)
{
}

const String PingPong2AudioProcessor::getProgramName(int index)
{
	return {};
}

void PingPong2AudioProcessor::changeProgramName(int index, const String& newName)
{
}

//==============================================================================
void PingPong2AudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
	mSampleRate = sampleRate;
	const int numInputChannels = getTotalNumInputChannels();
	const int delayBufferSize = 2 * (sampleRate * samplesPerBlock);

	myDelayBuffer.setSize(numInputChannels, delayBufferSize);
}

int PingPong2AudioProcessor::getNumParameters()
{
	return Parameters(numParameters);
}

float PingPong2AudioProcessor::getParameter(int index)
{
	switch (index)
	{
	case Parameters(gainParam): // exemplu
		return gain;
	default:
		return 0.0f; // index invalid
	}
}

void PingPong2AudioProcessor::setParameter(int index, float newValue)
{
	switch (index)
	{
	case Parameters(gainParam):
		gain = newValue;
		break;
	default:
		return;
	}
	UIUpdateFlag = true;//Request UI update -- Some OSX hosts use alternate editors, this updates ours
}

const String PingPong2AudioProcessor::getParameterName(int index)
{
	switch (index)
	{
	case Parameters(gainParam):
		return "Gain";
	default:
		return "";
	}
}

const String PingPong2AudioProcessor::getParameterText(int index)
{
	if (index >= 0 && index < numParameters)
		return String(Parameters(index));
	else
		return "";
}


void PingPong2AudioProcessor::releaseResources()
{
	// When playback stops, you can use this as an opportunity to free up any
	// spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool PingPong2AudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
#if JucePlugin_IsMidiEffect
	ignoreUnused(layouts);
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

void PingPong2AudioProcessor::processBlock(AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
	ScopedNoDenormals noDenormals;
	auto totalNumInputChannels = getTotalNumInputChannels();
	auto totalNumOutputChannels = getTotalNumOutputChannels();
	int mWritePosition;

	// In case we have more outputs than inputs, this code clears any output
	// channels that didn't contain input data, (because these aren't
	// guaranteed to be empty - they may contain garbage).
	// This is here to avoid people getting screaming feedback
	// when they first compile a plugin, but obviously you don't need to keep
	// this code if your algorithm always overwrites all the output channels.
	for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
		buffer.clear(i, 0, buffer.getNumSamples());

	// This is the place where you'd normally do the guts of your plugin's
	// audio processing...
	// Make sure to reset the state if your inner loop is processing
	// the samples and the outer loop is handling the channels.
	// Alternatively, you can process the samples with the channels
	// interleaved by keeping the same state.

	const int bufferLength = buffer.getNumSamples();
	const int delayBufferLength = myDelayBuffer.getNumSamples();

	for (int channel = 0; channel < totalNumInputChannels; ++channel)
	{

		std::cout << channel << std::endl;

		const float* bufferData = buffer.getReadPointer(channel);
		const float* delayBufferData = myDelayBuffer.getReadPointer(channel);
		float* dryBuffer = buffer.getWritePointer(channel);

		fillDelayBuffer(channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
		getFromDelayBuffer(buffer, channel, bufferLength, delayBufferLength, bufferData, delayBufferData);
		feedbackDelay(channel, bufferLength, delayBufferLength, bufferData, delayBufferData, dryBuffer);
	}

	mWritePosition += bufferLength;
	mWritePosition %= delayBufferLength;
}

void PingPong2AudioProcessor::fillDelayBuffer(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
	if (delayBufferLength > bufferLength + mWritePosition)
	{
		myDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, 0.8, 0.8);
	}
	else
	{
		const int bufferRemaining = delayBufferLength - mWritePosition;
		myDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, 0.8, 0.8);
		myDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength + bufferRemaining, 0.8, 0.8);
	}
}

void PingPong2AudioProcessor::getFromDelayBuffer(AudioBuffer<float> buffer, int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData)
{
	int delayTime = 500;
	const int readPosition = (int)(delayBufferLength + mWritePosition - (mSampleRate * delayTime / 1000)) % delayBufferLength;

	if (delayBufferLength > bufferLength + readPosition)
	{
		buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferLength);
	}
	else
	{
		const int bufferRemaining = delayBufferLength - readPosition;
		buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
		buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
	}

}

void PingPong2AudioProcessor::feedbackDelay(int channel, const int bufferLength, const int delayBufferLength, const float* bufferData, const float* delayBufferData, float* dryBuffer)
{
	if (delayBufferLength > bufferLength + mWritePosition)
	{
		myDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, 0.8, 0.8);
	}
	else
	{
		const int bufferRemaining = delayBufferLength - mWritePosition;

		myDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, 0.8, 0.8);
		myDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, 0.8, 0.8);
	}
}


//==============================================================================
bool PingPong2AudioProcessor::hasEditor() const
{
	return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* PingPong2AudioProcessor::createEditor()
{
	return new PingPong2AudioProcessorEditor(this);
}

//==============================================================================
void PingPong2AudioProcessor::getStateInformation(MemoryBlock& destData)
{
	// You should use this method to store your parameters in the memory block.
	// You could do that either as raw data, or use the XML or ValueTree classes
	// as intermediaries to make it easy to save and load complex data.

	// se salvează parametrii/datele utilizatorului din fișier
	XmlElement root("Root");
	XmlElement* el;
	el = root.createNewChildElement("Gain");
	el->addTextElement(String(Parameters(gainParam)));
	copyXmlToBinary(root, destData);
}

void PingPong2AudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
	// You should use this method to restore your parameters from this memory block,
	// whose contents will have been created by the getStateInformation() call.

	// se încarcă parametrii/datele utilizatorului din fișier
	std::unique_ptr<juce::XmlElement> pRoot = getXmlFromBinary(data, sizeInBytes);
	if (pRoot != NULL)
	{
		forEachXmlChildElement((*pRoot), pChild)
		{
			if (pChild->hasTagName("gain"))
			{
				String text = pChild->getAllSubText();
				setParameter(gain, text.getFloatValue());
			}
		}
		UIUpdateFlag = true; // cere update de la interfața grafică
	}
}


//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
	return new PingPong2AudioProcessor();
}