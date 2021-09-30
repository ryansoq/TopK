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
