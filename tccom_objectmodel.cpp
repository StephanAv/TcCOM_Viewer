#include "tccom_objectmodel.h"
#include <sstream>
#include <iostream>

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
    uint32_t nErr = AdsSyncReadReq(&m_amsAddr, 0x00000110, 0, sizeof(m_nTcComModules), &m_nTcComModules);

    uint8_t b_data[176];
    memset(&b_data, 0, sizeof(b_data));
    unsigned long pcbReturn;

    nErr = AdsSyncReadReqEx(&m_amsAddr, 0x00000110, 2, sizeof(b_data), b_data, &pcbReturn);

    TcComModule module = {};

    memcpy(&module, b_data, sizeof(module));
    int x = 3;
}
