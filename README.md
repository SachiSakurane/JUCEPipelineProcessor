# JUCEPipelineProcessor
こういう書き方ができる

```C++
void SidechainMixerAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& ) {
    decltype(auto) ioBus = getBusBuffer (buffer, true, 0);
    decltype(auto) pipeline = 
        ioBus | ProcessBlockInput{sharedBuffer} | PassBlock{} | ProcessBlockOutput{ioBus};
    pipeline.process();
}
```

令和らしくConceptsを使ってるので、あたらしめのコンパイラつかってね。
