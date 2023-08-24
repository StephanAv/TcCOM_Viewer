#include "tccom_objectmodel.h"
#include <sstream>
#include <iostream>
#include <vector>


TcComModule::TcComModule(uint8_t *b_data)
{
    this->class_id.data1 = *reinterpret_cast<uint32_t*>(b_data);
    this->class_id.data2 = *reinterpret_cast<uint16_t*>(b_data + 4);
    this->class_id.data3 = *reinterpret_cast<uint16_t*>(b_data + 6);
    this->class_id.data4 = *reinterpret_cast<uint16_t*>(b_data + 8);

    this->class_id.data5[0] = b_data[10];
    this->class_id.data5[1] = b_data[11];
    this->class_id.data5[2] = b_data[12];
    this->class_id.data5[3] = b_data[13];
    this->class_id.data5[4] = b_data[14];
    this->class_id.data5[5] = b_data[15];

    this->otcid  = *reinterpret_cast<uint32_t*>(b_data + 16);  // 16 - 19
    this->parent = *reinterpret_cast<uint32_t*>(b_data + 20); // 20 - 23
    this->refCnt = *reinterpret_cast<uint32_t*>(b_data + 24); // 24 - 27
    this->state  = *reinterpret_cast<uint32_t*>(b_data + 28);  // 28 - 31
    this->unknown_a = *reinterpret_cast<uint32_t*>(b_data + 32); // 32 - 35
    this->unknown_b = *reinterpret_cast<uint32_t*>(b_data + 36); // 36 - 39
    this->unknown_c = *reinterpret_cast<uint32_t*>(b_data + 40); // 40 - 43
    this->unknown_d = *reinterpret_cast<uint32_t*>(b_data + 44); // 44 - 47

    this->name  = std::string((char*)b_data+48, 128); // 48 - 176
}

TcCOM_ObjectModel::TcCOM_ObjectModel(const QString& amsNetId)
{
    size_t i = 0;
    std::istringstream s_amsAddr(amsNetId.toStdString());
    std::string token;

    while ((i < sizeof(m_amsAddr.netId)) && std::getline(s_amsAddr, token, '.')) {
        m_amsAddr.netId.b[i++] = std::stoi(token);
    }


    m_amsAddr.port = m_port;

    m_clientPort =  AdsPortOpen();
    // raise if == 0
    uint32_t nErr = 0;
    nErr = AdsSyncReadReq(&m_amsAddr, 0x00000110, 0, sizeof(m_nTcComModules), &m_nTcComModules);

    // 176 * 13

    //std::shared_ptr<TcCOM_ObjectModel>

    const size_t nData = 176 * m_nTcComModules;
    std::vector<uint8_t> data(nData);

    data[0] = 9;
    //uint8_t b_data[176];
    //memset(&b_data, 0, sizeof(b_data));
    unsigned long pcbReturn;

    nErr = AdsSyncReadReqEx(&m_amsAddr, 0x00000110, 2, data.size(), data.data(), &pcbReturn);
    if(nErr != ADSERR_NOERR){
        std::stringstream sErr;
        sErr << "ADS Error: 0x" << std::hex << nErr;
        std::cerr << sErr.str();
        throw std::runtime_error("sErr.str()");
    }



    for(int i = 0; i < m_nTcComModules; i++)
    {

        size_t addrOffs = i * 176;
        uint8_t *b_data = data.data() + addrOffs;
        uint8_t b_datatmp[176];
        memcpy(b_datatmp, b_data, 176);


        m_root.push_back(std::shared_ptr<TcComModule>(new TcComModule(b_data)));
    }

    // find and link parents


    int x = 3;
}
