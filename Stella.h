#ifndef STELLA_STELLA_H_
#define STELLA_STELLA_H_

#include <memory>

using namespace std;

enum HResult
{
	kSUCCESS = 0,
	kFAIL
};


struct BasePairIndex
{
	unsigned int code;
	unsigned long refPos;
	unsigned int offset;
	int count;
};

struct BasePairDiffMaker
{
	unsigned long ref_pos;
	char original_base_pair;
	char current_base_pair;
	char different;
};

struct AlignerResult {
	BasePairDiffMaker* base_pair_diff_maker;
	size_t diff_size;
	BasePairIndex* base_pair_index;
};
 
#endif //STELLA_STELLA_H_