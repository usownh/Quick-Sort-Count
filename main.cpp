#include <QFile>
#include <QList>
#include <QDebug>
#include <QTime>
int Partition(int list[],int start,int end,qint64& count,int buffer[])
{
    int pivot=list[start];
    int A=start,B=end;
    for(int i=start+1;i<=end;i++)
    {
        if(list[i]<=pivot)
        {
            buffer[A]=list[i];
            A++;
            count+=end-B+1;
        }
        else
        {
            buffer[B]=list[i];
            B--;
        }
    }
    list[A]=pivot;
    for(int i=start;i<A;i++) list[i]=buffer[i];
    for(int i=A+1;i<=end;i++) list[i]=buffer[end-i+B+1];
    return A;
}
void QuickSortAndCount(int list[],int start,int end,qint64& count,int buffer[])
{
    if(start<end)
    {
        int mid;
        mid=Partition(list,start,end,count,buffer);
        QuickSortAndCount(list,start,mid-1,count,buffer);
        QuickSortAndCount(list,mid+1,end,count,buffer);
    }
}
int main(int argc, char *argv[])
{
    QFile file;
    QList<int> list;
    file.setFileName("Q5.txt");
    file.open(QIODevice::ReadOnly);
    QString line;
    while(!file.atEnd())
    {
        line=file.readLine();
        list.append(line.toInt());
    }
    file.close();
    int intList[list.size()];
    int buffer[list.size()];
    for(int i=0;i<list.size();i++) intList[i]=list[i];
    qint64 count=0;
    qDebug()<<"start to sort";
    QTime start,end;
    start=QTime::currentTime();
    QuickSortAndCount(intList,0,list.size()-1,count,buffer);
    end=QTime::currentTime();
    qDebug()<<"the number of inversions is"<<count<<"using time:"<<start.msecsTo(end)<<"ms";
    return 0;
}
