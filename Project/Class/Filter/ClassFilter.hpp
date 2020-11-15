#include <string>
#include <gatb/gatb_core.hpp>

typedef Bloom<Kmer<>::Type> bloom_type;

class ClassFilter
{
    public:
    ClassFilter(int kmerSize, std::string bankTranscript, std::string bankSequences);
    void CreateBloomFilter();
    void Filter(float p);
    void CreateHashMap();
    void displayResult();
    list < list<std::string> > getResult();


    private:
    std::string m_bankTranscript;
    std::string m_bankSequences;
    int m_kmerSize;
    bloom_type *m_bloom;
    std::map<std::string, std::string> m_hashMapTranscript;
    list < list<std::string> > result;
    ofstream TransformationFile;

};