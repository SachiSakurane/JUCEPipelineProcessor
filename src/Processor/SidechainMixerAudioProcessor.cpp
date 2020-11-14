//
// Created by Himatya on 2020/10/30.
//

#include "SidechainMixerAudioProcessor.hpp"
#include "Constants.hpp"
#include "DSP/Invert.hpp"
#include "DSP/ProcessablePileline.hpp"

using namespace AudioProcessorExtensions;

struct SidechainMixerAudioProcessorStateInformation : StateInformationInterface {
    void getStateInformation (juce::MemoryBlock &destData) final {}
    void setStateInformation (const void *data, int sizeInBytes) final {}
};

struct SidechainMixerAudioProcessorData : DataInterface {
    const juce::String getName() const final {
        return JucePlugin_Name;
    }

    juce::StringArray getAlternateDisplayNames() const final {
        return {JucePlugin_Name, "SaniCon"};
    }

    bool acceptsMidi() const final {
        #if JucePlugin_WantsMidiInput
        return true;
        #else
        return false;
        #endif
    }

    bool producesMidi() const final {
        #if JucePlugin_ProducesMidiOutput
        return true;
        #else
        return false;
        #endif
    }

    bool isMidiEffect() const final {
        #if JucePlugin_IsMidiEffect
        return true;
        #else
        return false;
        #endif
    }

    bool isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout& layouts) const final {
        #if JucePlugin_IsMidiEffect
        ignoreUnused (layouts);
        return true;
        #else
        // This is the place where you check if the layout is supported.
        // In this template code we only support mono or stereo.
        if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
            && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
            return false;

        // This checks if the input layout matches the output layout
            #if ! JucePlugin_IsSynth
        if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
            return false;
            #endif

        return true;
        #endif
    }
};

struct SidechainMixerAudioProcessorDAWMessage : DAWMessageInterface {
    double getTailLengthSeconds() const final {
        return 0.0;
    }
};

struct SidechainMixerAudioProcessorProgram : ProgramInterface {
    int getNumPrograms() final {
        // NB: some hosts don't cope very well if you tell them there are 0 programs,
        // so this should be at least 1, even if you're not really implementing programs.
        return 1;
    }

    int getCurrentProgram() final {
        return 0;
    }

    void setCurrentProgram (int index) final {
    }

    const juce::String getProgramName (int index) final {
        return {};
    }

    void changeProgramName (int index, const juce::String& newName) final {}
};

SidechainMixerAudioProcessor::SidechainMixerAudioProcessor() :
    ProcessorType {
        juce::AudioProcessor::BusesProperties()
            #if !JucePlugin_IsMidiEffect
                #if !JucePlugin_IsSynth
            .withInput("Input", juce::AudioChannelSet::stereo(), true)
                #endif
            .withOutput("Output", juce::AudioChannelSet::stereo(), true)
            #endif
            .withInput("Sidechain", juce::AudioChannelSet::stereo(), true),
        std::make_unique<SidechainMixerAudioProcessorStateInformation>(),
        std::make_unique<SidechainMixerAudioProcessorData>(),
        std::make_unique<SidechainMixerAudioProcessorDAWMessage>(),
        std::make_unique<SidechainMixerAudioProcessorProgram>()
    }{
}

void SidechainMixerAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock) {
    sharedBuffer = std::make_shared<MultiBuffer<float>>(
        MultiBuffer<float>{
            {2,
             mk2::container::fixed_array<float>(static_cast<size_t>(samplesPerBlock),0.f)}
        });
}

void SidechainMixerAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer,
                                                 juce::MidiBuffer& midiMessages) {
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    decltype(auto) ioBus = getBusBuffer (buffer, true, 0);
    decltype(auto) inv = Invert{};
    inv.process(ioBus);
    Invert{}.process(ioBus);

    decltype(auto) pipelineL = ProcessableBinder{Invert{}, ioBus};
    pipelineL.process();
    decltype(auto) pipelineR = ioBus | Invert{};
    pipelineR.process();
}

void SidechainMixerAudioProcessor::releaseResources() {

}
