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
