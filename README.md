# Use decode_predictions to get Top1~TopK from model inference

## License

[!["THE SUSHI-WARE LICENSE"](https://img.shields.io/badge/license-SUSHI--WARE%F0%9F%8D%A3-blue.svg)](https://github.com/MakeNowJust/sushi-ware)

Below Markdown text says all about this license:

```markdown
## "THE SUSHI-WARE LICENSE"

<ryansoq@gmail.com> wrote this file.

As long as you retain this notice you can do whatever you want
with this stuff. If we meet some day, and you think this stuff
is worth it, you can buy me a **sushi 🍣** in return.

(This license is based on ["THE BEER-WARE LICENSE" (Revision 42)].
 Thanks a lot, Poul-Henning Kamp ;)

["THE BEER-WARE LICENSE" (Revision 42)]: https://people.freebsd.org/~phk/
```
## How to use

"imagenet1000_clsidx_to_labels.txt" content

```sh
0: 'tench, Tinca tinca',
1: 'goldfish, Carassius auratus',
2: 'great white shark, white shark, man-eater, man-eating shark, Carcharodon carcharias',
3: 'tiger shark, Galeocerdo cuvieri',
4: 'hammerhead, hammerhead shark',
5: 'electric ray, crampfish, numbfish, torpedo',
...
```

example code

```c++
#include <topk.h>

#define DATA_SIZE 5

int main(int argc, char *argv[])
{
    Tool tool;
    int8_t predictions[DATA_SIZE] = {63, 77, -88, 30, 56, }; // e.g. by some inference
    auto depredictions = tool.decode_predictions<int8_t, DATA_SIZE>(predictions, top = 5, "imagenet1000_clsidx_to_labels.txt");

    auto [index, label, value] = depredictions[0];
    std::cout << "The image prediction Top 1 index is: " << index << ", label name: " << label << ", confidence: " << (float)value << std::endl;

    return 0;
}
```
Predictions value [63, 77, -88, 30, 56, ...]

Print Top1~Top5 : 

```sh
Predicted: [
(1,  1: 'goldfish, Carassius auratus',, 77),
(0,  0: 'tench, Tinca tinca',, 63),
(4,  4: 'hammerhead, hammerhead shark',, 56),
(3,  3: 'tiger shark, Galeocerdo cuvieri',, 30),
(2,  2: 'great white shark, white shark, man-eater, man-eating shark, Carcharodon carcharias',, -88)]
The image prediction Top 1 index is: 1, label name:  1: 'goldfish, Carassius auratus',, confidence: 77
```

Note:

1. If you want to use BERT-Large, download their model into **coqa/bert-large-uncased**; if you want to use BERT-base, download their model into **coqa/bert-base-cased**;
    * The models can be downloaded from Huggingface:
      * 'bert-base-uncased': "https://s3.amazonaws.com/models.huggingface.co/bert/bert-base-uncased.tar.gz",
      * 'bert-large-uncased': "https://s3.amazonaws.com/models.huggingface.co/bert/bert-large-uncased.tar.gz"
    * bert-large-uncased-vocab.txt can be downloaded from Google's BERT repository
