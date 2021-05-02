# Guitar_amp

![alt](<Docs/Images/guitar_amp_image.png>)

This is a virtual guitar amplifier that was created using JUCE framework. 

GUI is split into four parts:

1. input volume:

   a) input volume knob

2. equalizer:

   a) low frequency band knob

   b) middle frequency band knob

   c) high frequency band knob

3. drive

   a) threshold knob

   b) comp knob

   c) plus wave

   d) minus wave

4. master volume

   a) master volume knob
   

Besides these part there are:

- cabinet simulation switch ON/OFF
- power/bypass switch ON/OFF



Drive function principle of operation based on saturation

![alt](<Docs/Images/nonlinear.png>)


To create project Guitar_amp use Projucer (from JUCE framework) and generate files to build.

To download executable .exe or .vst3 plugin check out releases on https://github.com/dkuzniar4/Guitar_amp2/releases/