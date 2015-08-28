#include "stdio.h"

#include "Stella.h"
#include "GeneDataExporter.h"
#include "SharedGeneData.h"
#include "FastqReader.h"
#include "BasePairSequence.h"
#include "BasePairSequenceAligner.h"

#define TEST_BY_BIGCAT
#ifdef TEST_BY_BIGCAT

#include "FastqReader.h"

#endif

void Run(char* genome_file, char* base_pair, char* duplicate_file, char* input_file);

int main(int argc, char* argv[]) 
{
    if (5 == argc && argv[1][0] == 'e')
    {
        // Argv[1] == e
        // Argv[2] == hg19
        // Argv[3] == basepair 
        // Argv[4] == duplicate
        GeneDataExporter exporter;
        FILE* file_hg19;

        fopen_s(&file_hg19, argv[2], "r");
        fseek(file_hg19, 0, SEEK_END);
        auto file_length = _ftelli64(file_hg19);
        char* buffer = new char[file_length] {};
        fseek(file_hg19, 0, SEEK_SET);
        fread_s(buffer, file_length, 1, file_length, file_hg19);
        fclose(file_hg19);

        exporter.ExportBasePairData(argv[3], buffer, file_length);
        exporter.ExportDuplicate(argv[4]);

        return 0;
    }
    else if(5 == argc)
    {
        // Argv[1] == hg19
        // Argv[2] == basepair
        // Argv[3] == duplicate 
        // Argv[4] == input files
        Run(argv[1], argv[2], argv[3], argv[4]); 
    }

    printf("argv errors...\r\n");

#ifdef TEST_BY_BIGCAT
    FastqReader test_reader;
    test_reader.Init();
    test_reader.SetData("F:\\STELLADATA\\test.fastq");
    test_reader.Next();
#endif

    return 0;
}

void Run(char* genome_file, char* base_pair, char* duplicate_file, char* input_file) 
{
    // Load static data 
    SharedGeneData::instance()->LoadFromFile(genome_file, base_pair, duplicate_file);

    // Init fastq reader
    FastqReader reader;
    reader.Init();
    reader.SetData(input_file);

    BasePairSequence* seq = nullptr;

    do
    {
        seq = reader.Next();

        if (nullptr == seq)break;
        
        BasePairSequenceAligner aligner;
        aligner.SetData(seq, SharedGeneData::instance());
        if (kFAIL == aligner.Search()) continue;
        if (kFAIL == aligner.Filter()) continue;
        if (kFAIL == aligner.Diff()) continue;

    } 
    while (1);


}