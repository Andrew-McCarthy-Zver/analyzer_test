#include <QCoreApplication>
#include <iostream>
#include <QFile>
#include <QRegularExpression>
#include "alglib\\stdafx.h"
#include "alglib\\dataanalysis.h"
#include "frame.h"
#include "graph.h"
#include "vertex.h"
#include "func.h"

const QString allFileToString(QFile &aFile)
{
    if (!aFile.open(QFile::ReadOnly | QFile::Text)) {
        std::cout << "Error opening file!" << std::endl;
        return NULL;
    }
    QTextStream in(&aFile);
    return in.readAll();
}

void framenull (Frame &frame)
{
    frame.fragnum = NULL;
    frame.more_fragments = NULL;
    frame.number = NULL;
    frame.offset = NULL;
    frame.ra = "NULL";
    frame.seqnum = NULL;
    frame.size = NULL;
    frame.ssid = "NULL";
    frame.ta = "NULL";
    frame.type = "NULL";
}

void Framesstat (QList <Frame> &frames, Graph &graph)
{
    double failframes = 0;
    double adrframes = 0;
    QList <QString> vx;
    int k = 1;
    foreach(Frame fr, frames)
    {
       if ( fr.type == "Fail") failframes++;
       if (fr.ra != "NULL" && fr.ta != "NULL")
       {
           adrframes++;
           graph.edges.append(fr);
           if (!vx.contains(fr.ta)) {vx.append(fr.ta); graph.vertexes.append(Vertex(k,fr.ta,fr.ssid,fr.type,fr.type == "Management/Beacon"?true:false));k++;} else  if (fr.type == "Management/Beacon") {graph.vertexes[vx.indexOf(fr.ta)].t_d = true; graph.vertexes[vx.indexOf(fr.ta)].ssid = fr.ssid; }
           if (!vx.contains(fr.ra)) {vx.append(fr.ra); graph.vertexes.append(Vertex(k,fr.ra,fr.ssid,fr.type,false));k++;}
       }

    }
   graph.Form();
}
void ReadLog(QList <Frame> &frames,QString path)
{
    QFile file(path);
    if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
    {
        int framescount = 0;
        Frame currentframe;
        QRegularExpression r_offset("Offset=");
        QRegularExpression r_size("Size=");
        QRegularExpression r_type("Type=");
        QRegularExpression r_more_fragments("More Fragments=");
        QRegularExpression r_ta("TA=");
        QRegularExpression r_ra("RA=");
        QRegularExpression r_ra_1("RA/BSSID=");
        QRegularExpression r_ta_2("TA/BSSID=");
        QRegularExpression r_seqnum("Seqnum");
        QRegularExpression r_fragnum("Fragnum=");
        QRegularExpression r_fcs("FCS=Fail");
        QRegularExpression r_ssid("SSID='");

        while(!file.atEnd())
        {
             QString line = file.readLine();
             if (r_offset.match(line).hasMatch())
             {
                 framenull(currentframe);
                 framescount++;
                 currentframe.number = framescount;
                 currentframe.offset =  (line.mid(line.indexOf("Offset=")+7,line.indexOf(",",line.indexOf("Offset=")+7) - (line.indexOf("Offset=")+7))).toDouble();
             }
             if (r_size.match(line).hasMatch())
             {
                 currentframe.size = (line.mid(line.indexOf("Size=")+5,line.indexOf(",",line.indexOf("Size=")+5) - (line.indexOf("Size=")+5))).toInt();
             }
             if (r_type.match(line).hasMatch())
             {
                 currentframe.type = line.mid(line.indexOf("Type=")+5,line.indexOf(",",line.indexOf("Type=")+5) - (line.indexOf("Type=")+5));
             }
             if (r_more_fragments.match(line).hasMatch())
             {
                 currentframe.more_fragments = (line.mid(line.indexOf("More Fragments=")+15,line.indexOf(",",line.indexOf("More Fragments=")+15) - (line.indexOf("More Fragments=")+15))).toInt();
             }
             if (r_ta.match(line).hasMatch())
             {
                 currentframe.ta = line.mid(line.indexOf("TA=")+3,17);
             }
             if (r_ra.match(line).hasMatch())
             {
                 currentframe.ra = line.mid(line.indexOf("RA=")+3,17);
             }
             if (r_ra_1.match(line).hasMatch())
             {
                 currentframe.ra= line.mid(line.indexOf("RA/BSSID=")+9,17);
             }
             if (r_ta_2.match(line).hasMatch())
             {
                 currentframe.ta= line.mid(line.indexOf("TA/BSSID=")+9,17);
             }
             if (r_seqnum.match(line).hasMatch())
             {
                 currentframe.seqnum= (line.mid(line.indexOf("Seqnum=")+7,line.indexOf(",",line.indexOf("Seqnum=")+7) - (line.indexOf("Seqnum=")+7))).toInt();
             }
             if (r_fragnum.match(line).hasMatch())
             {
                 currentframe.fragnum= (line.mid(line.indexOf("Fragnum=")+8,line.indexOf(",",line.indexOf("Fragnum=")+8) - (line.indexOf("Fragnum=")+8))).toInt();
             }
             if (r_fcs.match(line).hasMatch())
             {
                 currentframe.type = "Fail";
             }
             if (r_ssid.match(line).hasMatch())
             {
                 currentframe.ssid= line.mid(line.indexOf("SSID='")+6,line.indexOf(",",line.indexOf("SSID='")+6) - (line.indexOf("SSID='")+6)-1);
             }
             if (currentframe.offset != NULL && currentframe.type != "NULL")
             {
                 frames.append(currentframe);
                 framenull(currentframe);
             }


        }
        file.close();
    }
}

void Framesdata(Graph &graph, QList<QList<Frame>> &data)
{
    QRegularExpression r_dat("Data");
    QList<Frame> dat = graph.edges;
    int count = 1;
    bool mf = false;
    int seqnum;
    int count_2 =0;
    int k;
    int fragnum;
    foreach(Frame fr,dat)
    {
            for (int i=1;i<count&&i<8;i++)
            {
                if (fr.ra == dat[count-i-1].ra && fr.ta == dat[count-i-1].ta && fr.seqnum == dat[count-i-1].seqnum && fr.more_fragments == dat[count-i-1].more_fragments && fr.fragnum == dat[count-i-1].fragnum ) {dat.removeAt(count-i-1); count--;}
            }
            count++;
    }
    foreach(Frame fr,dat)
    {
           if (!mf && fr.more_fragments!=0 && fr.fragnum==0) {mf = true; seqnum = fr.seqnum; k = count_2; fragnum=0;}
           if (mf&&fr.seqnum==seqnum&&fr.fragnum>fragnum)
           {
               fragnum = fr.fragnum;
               if(fr.more_fragments==0) mf = false;
               dat[k].size += fr.size;
               dat.remove(count_2);
               count_2--;
           }
           count_2++;

    }
    int d = 0;
    foreach(Frame fr,dat)
    {
        if (!r_dat.match(fr.type).hasMatch() || fr.ta == "ff:ff:ff:ff:ff:ff" || fr.ra == "ff:ff:ff:ff:ff:ff")
        {
        dat.remove(d);
        d--;
        }
        d++;
    }
    int num = 0;
    foreach(Vertex v,graph.vertexes)
    {
        bool m = true;
        foreach(Frame fr,dat)
        {
            if  (fr.ta == v.address )
            {
                if (m) {data.append(QList<Frame>{fr}); num++;  m = false;}
                else
                data[num-1].append(fr);
            }
        }
    }
}

int compare(const void *a, const void *b)
{
    const double *ad, *bd;

    ad = (const double*)a;
    bd = (const double*)b;

    if (*ad < *bd)
    {
        return -1;
    }
    else if (*ad > *bd)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

void Standartfunction (double med[],int count, func &f,int k)
{
    qsort(med, count, sizeof(double), compare);
    double mean = 0;
    double median = 0;
    for (int i = 0; i < count; i++)
    {
        mean += med[i];
    }
    mean /= count;
    floor((count+1)/2) == (count+1)/2?median = med[int((count+1)/2)]:median = (med[int((count+1)/2)-1] + med[int((count+1)/2)])/2;
    double medad[count];
    for (int i = 0; i < count; i++)
    {
        medad[i]=fabs(med[i]-median);
    }
    qsort(medad, count, sizeof(double), compare);
    double medianad = 0;
    floor((count+1)/2) == (count+1)/2?medianad = medad[int((count+1)/2)]:medianad = (medad[int((count+1)/2)-1] + medad[int((count+1)/2)])/2;
    double sd = 0;
    double variance = 0;
    for (int i = 0; i < count; i++)
    {
        sd += pow(med[i]-mean,2);
    }
    variance = sd/(count -1);
    sd = sqrt(sd/(count - 1));
    double m_sq = 0;
    for (int i = 0; i < count; i++)
    {
        m_sq += pow(med[i],2);
    }
    m_sq = m_sq/count;
    double rms = sqrt(m_sq);
    double p_skewness = 3*(mean-median)/variance;
    double kurtosys = 0;
    double skewness = 0;
    for (int i = 0; i < count; i++)
    {
        kurtosys += pow((med[i]-mean)/variance,4);
        skewness += pow((med[i]-mean)/variance,3);
    }
    kurtosys =  kurtosys/count;
    skewness =  skewness/count;
    if (k==1){
        f.sd = sd;
        f.variance = variance;
        f.rms = rms;
        f.m_sq = m_sq;
        f.p_skewness = p_skewness;
        f.kurtosys = kurtosys;
        f.skewness = skewness;
        f.med_0 = med[0];
        f.med = med[count-1];
        f.mean = mean;
        f.median = median;
        f.medianad = medianad;
    }
    if (k==2){
        f.sd_2 = sd;
        f.variance_2 = variance;
        f.rms_2 = rms;
        f.m_sq_2 = m_sq;
        f.p_skewness_2 = p_skewness;
        f.kurtosys_2 = kurtosys;
        f.skewness_2 = skewness;
        f.med_0_2 = med[0];
        f.med_2 = med[count-1];
        f.mean_2 = mean;
        f.median_2 = median;
        f.medianad_2 = medianad;
    }
}

void Framessamples(QList<QList<Frame>> &data,QList<QList<func>> &samples_func)
{
    QList<QList<QList<Frame>>> samples;
    foreach (QList<Frame> frames,data)
    {
        int num = 0;
        int size = frames.size();
        int count = 1;
        QList<QList<Frame>> sampl;
        sampl.append(QList<Frame>{frames[0]});
        while (count < size)
        {
            if (count+20<size)
            {
                for (int i =1; i<20;i++)
                {
                    sampl[num].append(frames[count]);
                    count++;
                }
                count -= 13;
                sampl.append(QList<Frame>{frames[count]});
                count ++;
                num++;
            }
            else
            {
                for(int i=0;i<size-count;i++)
                {
                    sampl[num].append(frames[count]);
                    count++;
                }
            }
        }
        samples.append(sampl);
    }

   foreach(QList<QList<Frame>> devices,samples)
    {
        QList<func> funcs;
        int k = 1;
        double mtu = 0;
        foreach(QList<Frame> sample,devices)
        {
            k++;
            int count = 0;
            double med[sample.size()];
            double offsets[sample.size()];
            int allsize = 0;
            double pivotsize = 0;
            bool notpivotsize = false;
            foreach(Frame fr, sample)
            {
                allsize += fr.size;
                med[count] = fr.size;
                offsets[count] = fr.offset;
                if (fr.size>mtu) mtu = fr.size;
                if (count==1 && sample.size()>count+1)
                {
                    if (fr.size < mtu && sample[count+1].size == mtu && sample[count-1].size==mtu )
                    {
                        if (pivotsize==0||fr.size == pivotsize) { pivotsize = fr.size; }
                        else {notpivotsize = true;}
                    }
                }
                else if (count ==2 && sample.size()>count+1)
                {
                    if (fr.size < mtu && sample[count+1].size == mtu && (sample[count-1].size==mtu||sample[count-2].size==mtu) )
                    {
                        if (pivotsize==0||fr.size == pivotsize) { pivotsize = fr.size; }
                        else {notpivotsize = true;}
                    }
                }
                else if (count>2 && count <19 && sample.size()>count+1)
                {
                    if (fr.size < mtu && sample[count+1].size == mtu && (sample[count-1].size==mtu||sample[count-2].size==mtu|| sample[count-3].size==mtu) )
                    {
                        if (pivotsize==0||fr.size == pivotsize) { pivotsize = fr.size; }
                        else {notpivotsize = true;}
                    }
                }
                count++;

            }
            if (notpivotsize) pivotsize = 0;
            func f;
            double pm = pivotsize/mtu;
            double pt = pivotsize/allsize;
            Standartfunction(med,count,f,1);
            Standartfunction(offsets,count,f,2);
            f.ta = devices[0][0].ta;
            f.ra = devices[0][0].ra;
            f.pivotsize = pivotsize;
            f.pm = pm;
            f.pt = pt;
            funcs.append(f);
        }
        samples_func.append(funcs);
    }
}

void Savefunc(QList<QList<func>> &samples_func, QString path)
{
    QRegularExpression f("/fram.+.log");
    path.remove(f);
    QFile file(path+"/func.log");
    if (file.open(QIODevice::WriteOnly))
        {
            QTextStream out(&file);
            if (samples_func[0].count()>samples_func[1].count())
            {
                int m = 0;
                foreach (func f,samples_func[0])
                {
                    if (m==0) out << f.pivotsize << " " << f.pm << " " << f.pt << " " << f.sd << " " << f.variance << " " << f.rms << " " << f.m_sq << " " << f.p_skewness << " " << f.kurtosys << " " << f.skewness << " " << f.med_0 << " " << f.med << " " << f.mean  << " " << f.median << " " << f.medianad << " " << f.sd_2 << " " << f.variance_2 << " " << f.rms_2 << " " << f.m_sq_2 << " " << f.p_skewness_2 << " " << f.kurtosys_2 << " " << f.skewness_2 << " " << f.med_0_2 << " " << f.med_2 << " " << f.mean_2  << " " << f.median_2 << " " << f.medianad_2 << " " ;
                    else out << "\n" << f.pivotsize << " " << f.pm << " " << f.pt << " " << f.sd << " " << f.variance << " " << f.rms << " " << f.m_sq << " " << f.p_skewness << " " << f.kurtosys << " " << f.skewness << " " << f.med_0 << " " << f.med << " " << f.mean  << " " << f.median << " " << f.medianad << " " << f.sd_2 << " " << f.variance_2 << " " << f.rms_2 << " " << f.m_sq_2 << " " << f.p_skewness_2 << " " << f.kurtosys_2 << " " << f.skewness_2 << " " << f.med_0_2 << " " << f.med_2 << " " << f.mean_2  << " " << f.median_2 << " " << f.medianad_2 << " " ;
                    m++;
                }
            }
            else
            {
                int m = 0;
                foreach (func f,samples_func[1])
                {
                    if (m==0) out << f.pivotsize << " " << f.pm << " " << f.pt << " " << f.sd << " " << f.variance << " " << f.rms << " " << f.m_sq << " " << f.p_skewness << " " << f.kurtosys << " " << f.skewness << " " << f.med_0 << " " << f.med << " " << f.mean  << " " << f.median << " " << f.medianad << " " << f.sd_2 << " " << f.variance_2 << " " << f.rms_2 << " " << f.m_sq_2 << " " << f.p_skewness_2 << " " << f.kurtosys_2 << " " << f.skewness_2 << " " << f.med_0_2 << " " << f.med_2 << " " << f.mean_2  << " " << f.median_2 << " " << f.medianad_2 << " " ;
                    else out << "\n" << f.pivotsize << " " << f.pm << " " << f.pt << " " << f.sd << " " << f.variance << " " << f.rms << " " << f.m_sq << " " << f.p_skewness << " " << f.kurtosys << " " << f.skewness << " " << f.med_0 << " " << f.med << " " << f.mean  << " " << f.median << " " << f.medianad << " " << f.sd_2 << " " << f.variance_2 << " " << f.rms_2 << " " << f.m_sq_2 << " " << f.p_skewness_2 << " " << f.kurtosys_2 << " " << f.skewness_2 << " " << f.med_0_2 << " " << f.med_2 << " " << f.mean_2  << " " << f.median_2 << " " << f.medianad_2 << " " ;
                    m++;
                }
            }
        }

}

void menu()
{
    int choice;
        do
        {
            std::cout << "Menu:\n1. Check existing files from 'test' folder\n2. Select a file to check\n3. Close\n" << std::endl;
            std::cin >> choice;
            switch (choice)
            {
            case 1:
            {
              QString path = "./datasets/train/func.log";
              QFile file(path);
              QStringList aStringList = allFileToString(file).split("\n");
              size_t col_line = aStringList.size() - 1; // Count of line
              size_t col_digits = aStringList.at(0).count(" ") + 1; // Count of digits in line
              alglib::decisionforestbuilder builder;
              alglib::ae_int_t nvars = 27;
              alglib::ae_int_t nclasses = 2;
              alglib::real_2d_array train;
              alglib::ae_int_t npoints;
              npoints = col_line;
              train.setlength(npoints,nvars+1);
              for (size_t i = 0; i < col_line; ++i) {
                     for (size_t j = 0; j < col_digits; ++j) {
                         train(i,j) = aStringList.at(i).split(" ").at(j).toInt();
                     }
                 }
              dfbuildercreate(builder);
              dfbuildersetdataset(builder, train, npoints, nvars, nclasses);
              alglib::ae_int_t ntrees = 100;
              alglib::decisionforest forest;
              alglib::dfreport rep;
              dfbuilderbuildrandomforest(builder, ntrees, forest, rep);

              QString path_2[6] =
              {
                  "./datasets/drones/dji_mavic_air/handshake-work-goodbye.pcm/func.log",
                  "./datasets/drones/dji_tello/18_01_45 2427MHz 23312.5KHz.pcm/func.log",
                  "./datasets/drones/syma_x5_sw/10_24_27 2439.346405MHz 93250.000000KHz.pcm/func.log",
                  "./datasets/drones/syma_x5_uw/10_31_11 2439.346405MHz 93250.000000KHz.pcm/func.log",
                  "./datasets/drones/wltoys_q242/10_39_38 2439.346405MHz 93250.000000KHz(Video).pcm/func.log",
                  "./datasets/drones/xiaomi_mi_drone_4k/13_40_03 5765.117978MHz 13321.428571KHz.pcm/func.log",

              };
              QString path_3[7] =
              {
                  "./datasets/non-drones/droidcam_voip/func.log",
                  "./datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/func.log",
                  "./datasets/non-drones/test_pdf/func.log",
                  "./datasets/non-drones/test_ping/func.log",
                  "./datasets/non-drones/test_twitch/func.log",
                  "./datasets/non-drones/test_yandex_maps/func.log",
                  "./datasets/non-drones/test_youtube/func.log",

              };
              QString namenondrones[7] =
              {
                  "droidcam_voip",
                  "test_download_app",
                  "test_pdf",
                  "test_ping",
                  "test_twitch",
                  "test_yandex_maps",
                  "test_youtube",
              };
              QString namedrones[6] =
              {
                  "dji_mavic_air",
                  "dji_tello",
                  "syma_x5_sw",
                  "syma_x5_uw",
                  "wltoys_q242",
                  "xiaomi_mi_drone_4k",
              };
                qDebug() << "Hypothesis drone:\n";
              for (int m = 0; m < 6;m++){
              QFile file_2(path_2[m]);
              QStringList aStringList_2 = allFileToString(file_2).split("\n");
              size_t col_line_2 = aStringList_2.size(); // Count of line
              size_t col_digits_2 = aStringList_2.at(0).count(" ") + 1;
              alglib::real_1d_array e;
              e.setlength(27);
              float tr = 0;
              float fl = 0;
              for (size_t i = 0; i < col_line_2; ++i) {
                     for (size_t j = 0; j < col_digits_2; ++j) {
                         e(j) = aStringList_2.at(i).split(" ").at(j).toInt();
                     }
                     alglib::ae_int_t v;
                     v = dfclassify(forest, e);
                     if (v==1) tr++; else fl++;
                 }
                  float pr  = tr/(tr+fl)*100;
                 qDebug() << namedrones[m]<< ": Drone detected in " << tr << "("<<pr<<"%) samples.\n";}
              qDebug() << "Hypothesis non-drone:\n";
            for (int m = 0; m < 7;m++){
            QFile file_2(path_3[m]);
            QStringList aStringList_2 = allFileToString(file_2).split("\n");
            size_t col_line_2 = aStringList_2.size(); // Count of line
            size_t col_digits_2 = aStringList_2.at(0).count(" ") + 1;
            alglib::real_1d_array e;
            e.setlength(27);
            float tr = 0;
            float fl = 0;
            for (size_t i = 0; i < col_line_2; ++i) {
                   for (size_t j = 0; j < col_digits_2; ++j) {
                       e(j) = aStringList_2.at(i).split(" ").at(j).toInt();
                   }
                   alglib::ae_int_t v;
                   v = dfclassify(forest, e);
                   if (v==1) tr++; else fl++;
               }
                float pr  = tr/(tr+fl)*100;
               qDebug() << namenondrones[m]<< ": Drone detected in " << tr << "("<<pr<<"%) samples.\n";}

              break;
            }
            case 2:
            {
                std::string path;
                std::cout << "Enter the full path to the file" << std::endl;
                std::cin >> path;
                QList <Frame> frames;
                Graph graph;
                QList<QList<Frame>> data;
                ReadLog(frames,QString::fromStdString(path));
                Framesstat(frames,graph);
                Framesdata(graph,data);
                QList<QList<func>> samples_func;
                Framessamples(data,samples_func);
                Savefunc(samples_func,QString::fromStdString(path));
                QString path_2 = "./datasets/train/func.log";
                QFile file(path_2);
                QStringList aStringList = allFileToString(file).split("\n");
                size_t col_line = aStringList.size() - 1; // Count of line
                size_t col_digits = aStringList.at(0).count(" ") + 1; // Count of digits in line
                alglib::decisionforestbuilder builder;
                alglib::ae_int_t nvars = 27;
                alglib::ae_int_t nclasses = 2;
                alglib::real_2d_array train;
                alglib::ae_int_t npoints;
                npoints = col_line;
                train.setlength(npoints,nvars+1);
                for (size_t i = 0; i < col_line; ++i) {
                       for (size_t j = 0; j < col_digits; ++j) {
                           train(i,j) = aStringList.at(i).split(" ").at(j).toInt();
                       }
                   }
                dfbuildercreate(builder);
                dfbuildersetdataset(builder, train, npoints, nvars, nclasses);
                alglib::ae_int_t ntrees = 100;
                alglib::decisionforest forest;
                alglib::dfreport rep;
                dfbuilderbuildrandomforest(builder, ntrees, forest, rep);
                QRegularExpression f("/fram.+.log");
                QString path_3 = QString::fromStdString(path).remove(f) + "/func.log";
                QFile file_2(path_3);
                QStringList aStringList_2 = allFileToString(file_2).split("\n");
                size_t col_line_2 = aStringList_2.size(); // Count of line
                size_t col_digits_2 = aStringList_2.at(0).count(" ") + 1;
                alglib::real_1d_array e;
                e.setlength(27);
                float tr = 0;
                float fl = 0;
                for (size_t i = 0; i < col_line_2; ++i) {
                       for (size_t j = 0; j < col_digits_2; ++j) {
                           e(j) = aStringList_2.at(i).split(" ").at(j).toInt();
                       }
                       alglib::ae_int_t v;
                       v = dfclassify(forest, e);
                       if (v==1) tr++; else fl++;
                   }
                    float pr  = tr/(tr+fl)*100;
                   qDebug() << "Drone detected in " << tr << "("<<pr<<"%) samples.\n";
                break;
            }
            case 3:
                choice = 0;
                break;
             }

        } while (choice != 0);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    menu();

    return a.exec();
}

