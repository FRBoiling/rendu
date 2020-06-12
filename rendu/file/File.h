//
// Created by boil on 18-8-23.
//

#ifndef RENDU_FILE_H
#define RENDU_FILE_H

using namespace std;

namespace rendu
{
    class File : noncopyable
    {
    public:
        File(const char *file)
            : fp_(::fopen(file, "rb"))
        {
        }

        ~File()
        {
            if (fp_)
            {
                ::fclose(fp_);
            }
        }

        bool valid() const;
        string File::readBytes(int n);
        int32_t File::readInt32();
        uint8_t File::readUInt8();

    private:
        FILE *fp_;
    };

} // namespace rendu
#endif //RENDU_FILE_FILE_H
