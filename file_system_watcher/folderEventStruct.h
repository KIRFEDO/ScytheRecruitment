#ifndef FOLDEREVENTSTRUCT_H
#define FOLDEREVENTSTRUCT_H

#include <QString>

struct FolderEventStruct{
    QString type, path, timestamp;
    bool isFolder;
    FolderEventStruct(QString type, QString path, QString timestamp, bool isFolder){
        this->type=type;
        this->path=path;
        this->timestamp=timestamp;
        this->isFolder=isFolder;
    }
    QString getColValue(const int index, const bool isHeader) const{
        if(isHeader){
            switch(index){
                case 0:
                    return "Event type";
                case 1:
                    return "Path";
                case 2:
                    return "Is folder";
                case 3:
                    return "Timestamp";
                default:
                    return "err";
            }
        } else {
            switch(index){
                case 0:
                    return type;
                case 1:
                    return path;
                case 2:
                    return isFolder ? "Yes" : "No";
                case 3:
                    return timestamp;
                default:
                return "err";
            }
        }
    }
};

#endif // FOLDEREVENTSTRUCT_H
