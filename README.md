# JUCEPipelineProcessor
こういう書き方ができる

```C++
void SidechainMixerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& ) {
    decltype(auto) ioBus = getBusBuffer (buffer, true, 0);
    decltype(auto) sidechainBus = getBusBuffer (buffer, true, 1);

    decltype(auto) pipeline = ioBus | Mix { sidechainBus, 0.5 };
    pipeline.process();
}
```

令和らしくConceptsを使ってるので、あたらしめのコンパイラつかってね。
