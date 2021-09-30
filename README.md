# Use decode_predictions to get Top1~TopK from model inference

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
    auto top = tool.decode_predictions<int8_t, DATA_SIZE>(predictions, "imagenet1000_clsidx_to_labels.txt");

    for (int i = 0; i < DATA_SIZE; i++)
    {
        auto [index, label, value] = top[i];
        std::cout << "The image prediction Top " << i + 1 << " is id: " << index << ", name: " << label << ", confidence: " << (float)value << std::endl;
    }
    return 0;
}
```
Predictions value [63, 77, -88, 30, 56, ...]

Print Top1~Top5 : 

```sh
The image prediction Top 1 is id: 1, name:  1: 'goldfish, Carassius auratus',, confidence: 77
The image prediction Top 2 is id: 0, name:  0: 'tench, Tinca tinca',, confidence: 63
The image prediction Top 3 is id: 4, name:  4: 'hammerhead, hammerhead shark',, confidence: 56
The image prediction Top 4 is id: 3, name:  3: 'tiger shark, Galeocerdo cuvieri',, confidence: 30
The image prediction Top 5 is id: 2, name:  2: 'great white shark, white shark, man-eater, man-eating shark, Carcharodon carcharias',, confidence: -88
```
