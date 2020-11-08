//
// Created by Himatya on 2020/10/26.
//

#pragma once

#include <cassert>

#include "DataInterface.hpp"
#include "DAWMessageInterface.hpp"
#include "StateInformationInterface.hpp"
#include "ProgramInterface.hpp"

namespace AudioProcessorExtensions
{
    template <
        class StateInformationInterfaceType = AudioProcessorExtensions::StateInformationInterface,
        class DataInterfaceType = AudioProcessorExtensions::DataInterface,
        class DAWMessageInterfaceType = AudioProcessorExtensions::DAWMessageInterface,
        class ProgramInterfaceType = AudioProcessorExtensions::ProgramInterface>
    class Processor : public juce::AudioProcessor
    {
    public:
        using ProcessorType = Processor<
            StateInformationInterfaceType,
            DataInterfaceType,
            DAWMessageInterfaceType,
            ProgramInterfaceType>;

        Processor (
            const BusesProperties &ioLayouts,
            std::unique_ptr<StateInformationInterfaceType> &&lifecycleInterface,
            std::unique_ptr<DataInterfaceType> &&dataInterface,
            std::unique_ptr<DAWMessageInterfaceType> &&messageInterface,
            std::unique_ptr<ProgramInterfaceType> &&programInterface) :
            juce::AudioProcessor {ioLayouts},
            lifecycle{std::move(lifecycleInterface)},
            data{std::move(dataInterface)},
            message{std::move(messageInterface)},
            program{std::move(programInterface)}
        {
            assert(lifecycle);
            assert(data);
            assert(message);
            assert(program);
        }

    protected:
        std::unique_ptr<StateInformationInterfaceType> lifecycle;
        std::unique_ptr<DataInterfaceType> data;
        std::unique_ptr<DAWMessageInterfaceType> message;
        std::unique_ptr<ProgramInterfaceType> program;

    private:
        const juce::String getName () const final
        {
            return data->getName();
        }

        juce::StringArray getAlternateDisplayNames () const final
        {
            return data->getAlternateDisplayNames();
        }

        bool acceptsMidi () const final
        {
            return data->acceptsMidi();
        }

        bool producesMidi () const final
        {
            return data->producesMidi();
        }

        bool isMidiEffect () const final
        {
            return data->isMidiEffect();
        }

        #ifndef JucePlugin_PreferredChannelConfigurations
        bool isBusesLayoutSupported (const juce::AudioProcessor::BusesLayout &layouts) const final
        {
            return data->isBusesLayoutSupported(layouts);
        }
        #endif

        double getTailLengthSeconds () const final
        {
            return message->getTailLengthSeconds();
        }

        void getStateInformation (juce::MemoryBlock &destData) final
        {
            lifecycle->getStateInformation(destData);
        }

        void setStateInformation (const void *data, int sizeInBytes) final
        {
            lifecycle->setStateInformation(data, sizeInBytes);
        }

        int getNumPrograms () final
        {
            return program->getNumPrograms();
        }

        int getCurrentProgram () final
        {
            return program->getCurrentProgram();
        }

        void setCurrentProgram (int index) final
        {
            program->setCurrentProgram(index);
        }

        const juce::String getProgramName (int index) final
        {
            return program->getProgramName(index);
        }

        void changeProgramName (int index, const juce::String &newName) final
        {
            program->changeProgramName(index, newName);
        }

        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Processor)
    };
}
