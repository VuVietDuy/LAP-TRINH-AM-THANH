#include <bits/stdc++.h>
#include <vector>

using namespace std;

// Cấu trúc header file wav
typedef struct {
    char riff[4]; // "RIFF"
    int file_size; // Kích thước file
    char wave[4]; // "WAVE"
    char fmt[4]; // "fmt "
    int fmt_size; // Kích thước chunk fmt
    short format; // Định dạng âm thanh (1 = PCM)
    short channels; // Số kênh
    int sample_rate; // Tần số lấy mẫu
    int byte_rate; // Tốc độ bit
    short block_align; // Căn chỉnh khối
    short bits_per_sample; // Độ sâu bit
    char data[4]; // "data"
    int data_size; // Kích thước chunk data
} WAV_HEADER;


void echo(vector<short>& data, int delay, float feedback) {
    for (int i = delay; i < data.size(); i++) {
        data[i] += feedback * data[i - delay];
    }
}


int main() {
    WAV_HEADER header;
    FILE *file;


    // Mở file
    file = fopen("D:\\PTIT\\LAP TRINH AM THANH\\MiniProject1\\input.wav", "rb");
    if (file == NULL) {
        printf("Error opening file\n");
        return 1;
    }

    // Đọc header
    fread(&header, sizeof(WAV_HEADER), 1, file);

    // In ra thông tin
    printf("RIFF chunk ID: %s\n", header.riff);
    printf("File size: %d\n", header.file_size);
    printf("WAVE chunk ID: %s\n", header.wave);
    printf("fmt chunk ID: %s\n", header.fmt);
    printf("fmt chunk size: %d\n", header.fmt_size);
    printf("Audio format: %d\n", header.format);
    printf("Number of channels: %d\n", header.channels);
    printf("Sample rate: %d\n", header.sample_rate);
    printf("Byte rate: %d\n", header.byte_rate);
    printf("Block align: %d\n", header.block_align);
    printf("Bits per sample: %d\n", header.bits_per_sample);
    printf("data chunk ID: %s\n", header.data);
    printf("Data size: %d\n", header.data_size);


    int num_samples = header.data_size / (header.bits_per_sample / 8);
    vector<short> audio_data(num_samples);

    // Seek to data chunk
    fseek(file, sizeof(WAV_HEADER), SEEK_SET);

    // Read audio data
    fread(&audio_data[0], sizeof(short), num_samples, file);

    // In ra một số mẫu đầu tiên
    for (int i = 0; i < 1000; i++) {
        cout << audio_data[i] << " ";
    }
    cout << "\n";


    // Đóng file
    fclose(file);
    return 0;
}

