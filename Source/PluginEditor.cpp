/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.4.5

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library.
  Copyright (c) 2017 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "PluginEditor.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PingPong2AudioProcessorEditor::PingPong2AudioProcessorEditor (PingPong2AudioProcessor* ownerFilter)
    : AudioProcessorEditor(ownerFilter)
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    gainSlider.reset (new Slider ("Slider Nivel"));
    addAndMakeVisible (gainSlider.get());
    gainSlider->setRange (-70, 0, 1);
    gainSlider->setSliderStyle (Slider::LinearHorizontal);
    gainSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 80, 20);
    gainSlider->addListener (this);

    gainSlider->setBounds (160, 64, 432, 112);

    gainLabel.reset (new Label ("Gain Label",
                                TRANS("Nivel")));
    addAndMakeVisible (gainLabel.get());
    gainLabel->setFont (Font (40.00f, Font::plain).withTypefaceStyle ("Regular"));
    gainLabel->setJustificationType (Justification::centredLeft);
    gainLabel->setEditable (false, false, false);
    gainLabel->setColour (Label::backgroundColourId, Colours::aliceblue);
    gainLabel->setColour (Label::textColourId, Colours::black);
    gainLabel->setColour (Label::outlineColourId, Colours::aliceblue);
    gainLabel->setColour (TextEditor::textColourId, Colours::black);
    gainLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    gainLabel->setBounds (56, 88, 96, 64);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
	getProcessor()->RequestUIUpdate();
	startTimer(200);
    //[/Constructor]
}

PingPong2AudioProcessorEditor::~PingPong2AudioProcessorEditor()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    gainSlider = nullptr;
    gainLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PingPong2AudioProcessorEditor::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::coral);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PingPong2AudioProcessorEditor::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PingPong2AudioProcessorEditor::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
	PingPong2AudioProcessor* ourProcessor = getProcessor();
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == gainSlider.get())
    {
        //[UserSliderCode_gainSlider] -- add your slider handling code here..
		ourProcessor->setParameter(PingPong2AudioProcessor::gain, (float)gainSlider->getValue());
        //[/UserSliderCode_gainSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PingPong2AudioProcessorEditor::timerCallback()
{
	PingPong2AudioProcessor* ourProcessor = getProcessor();
	//se schimba datele dorite intre elementele interfetei grafice si modulul “ourProcessor”

	if (ourProcessor->NeedsUIUpdate())
	{
		gainSlider->setValue(ourProcessor->getParameter(PingPong2AudioProcessor::gain), juce::dontSendNotification);
		ourProcessor->ClearUIUpdateFlag();
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PingPong2AudioProcessorEditor"
                 componentName="" parentClasses="public AudioProcessorEditor, public Timer"
                 constructorParams="PingPong2AudioProcessor* ownerFilter" variableInitialisers="AudioProcessor(ownerFilter)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffff7f50"/>
  <SLIDER name="Slider Nivel" id="7b656609696b9266" memberName="gainSlider"
          virtualName="" explicitFocusOrder="0" pos="160 64 432 112" min="-70.0"
          max="0.0" int="1.0" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="80" textBoxHeight="20" skewFactor="1.0"
          needsCallback="1"/>
  <LABEL name="Gain Label" id="b30406679d88a080" memberName="gainLabel"
         virtualName="" explicitFocusOrder="0" pos="56 88 96 64" bkgCol="fff0f8ff"
         textCol="ff000000" outlineCol="fff0f8ff" edTextCol="ff000000"
         edBkgCol="0" labelText="Nivel" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="40.0"
         kerning="0.0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]

