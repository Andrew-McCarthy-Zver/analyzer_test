QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        alglib/alglibinternal.cpp \
        alglib/alglibmisc.cpp \
        alglib/ap.cpp \
        alglib/dataanalysis.cpp \
        alglib/diffequations.cpp \
        alglib/fasttransforms.cpp \
        alglib/integration.cpp \
        alglib/interpolation.cpp \
        alglib/kernels_avx2.cpp \
        alglib/kernels_fma.cpp \
        alglib/kernels_sse2.cpp \
        alglib/linalg.cpp \
        alglib/optimization.cpp \
        alglib/solvers.cpp \
        alglib/specialfunctions.cpp \
        alglib/statistics.cpp \
        frame.cpp \
        func.cpp \
        graph.cpp \
        main.cpp \
        vertex.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    alglib/alglibinternal.h \
    alglib/alglibmisc.h \
    alglib/ap.h \
    alglib/dataanalysis.h \
    alglib/diffequations.h \
    alglib/fasttransforms.h \
    alglib/integration.h \
    alglib/interpolation.h \
    alglib/kernels_avx2.h \
    alglib/kernels_fma.h \
    alglib/kernels_sse2.h \
    alglib/linalg.h \
    alglib/optimization.h \
    alglib/solvers.h \
    alglib/specialfunctions.h \
    alglib/statistics.h \
    alglib/stdafx.h \
    frame.h \
    func.h \
    graph.h \
    vertex.h

DISTFILES += \
    datasets/drones/dji_mavic_air/handshake-work-goodbye.pcm/frames.log \
    datasets/drones/dji_mavic_air/handshake-work-goodbye.pcm/frames.pcap \
    datasets/drones/dji_mavic_air/handshake-work-goodbye.pcm/frames_parser.log \
    datasets/drones/dji_mavic_air/handshake-work-goodbye.pcm/frames_phy.log \
    datasets/drones/dji_mavic_air/handshake-work-goodbye.pcm/func.log \
    datasets/drones/dji_tello/18_01_45 2427MHz 23312.5KHz.pcm/frames.log \
    datasets/drones/dji_tello/18_01_45 2427MHz 23312.5KHz.pcm/frames.pcap \
    datasets/drones/dji_tello/18_01_45 2427MHz 23312.5KHz.pcm/frames_parser.log \
    datasets/drones/dji_tello/18_01_45 2427MHz 23312.5KHz.pcm/frames_phy.log \
    datasets/drones/dji_tello/18_01_45 2427MHz 23312.5KHz.pcm/func.log \
    datasets/drones/syma_x5_sw/10_24_27 2439.346405MHz 93250.000000KHz.pcm/frames.log \
    datasets/drones/syma_x5_sw/10_24_27 2439.346405MHz 93250.000000KHz.pcm/frames.pcap \
    datasets/drones/syma_x5_sw/10_24_27 2439.346405MHz 93250.000000KHz.pcm/frames_parser.log \
    datasets/drones/syma_x5_sw/10_24_27 2439.346405MHz 93250.000000KHz.pcm/frames_phy.log \
    datasets/drones/syma_x5_sw/10_24_27 2439.346405MHz 93250.000000KHz.pcm/func.log \
    datasets/drones/syma_x5_uw/10_31_11 2439.346405MHz 93250.000000KHz.pcm/frames.log \
    datasets/drones/syma_x5_uw/10_31_11 2439.346405MHz 93250.000000KHz.pcm/frames.pcap \
    datasets/drones/syma_x5_uw/10_31_11 2439.346405MHz 93250.000000KHz.pcm/frames_parser.log \
    datasets/drones/syma_x5_uw/10_31_11 2439.346405MHz 93250.000000KHz.pcm/frames_phy.log \
    datasets/drones/syma_x5_uw/10_31_11 2439.346405MHz 93250.000000KHz.pcm/func.log \
    datasets/drones/wltoys_q242/10_39_38 2439.346405MHz 93250.000000KHz(Video).pcm/frames.log \
    datasets/drones/wltoys_q242/10_39_38 2439.346405MHz 93250.000000KHz(Video).pcm/frames.pcap \
    datasets/drones/wltoys_q242/10_39_38 2439.346405MHz 93250.000000KHz(Video).pcm/frames_parser.log \
    datasets/drones/wltoys_q242/10_39_38 2439.346405MHz 93250.000000KHz(Video).pcm/frames_phy.log \
    datasets/drones/wltoys_q242/10_39_38 2439.346405MHz 93250.000000KHz(Video).pcm/func.log \
    datasets/drones/xiaomi_mi_drone_4k/13_40_03 5765.117978MHz 13321.428571KHz.pcm/frames.log \
    datasets/drones/xiaomi_mi_drone_4k/13_40_03 5765.117978MHz 13321.428571KHz.pcm/frames.pcap \
    datasets/drones/xiaomi_mi_drone_4k/13_40_03 5765.117978MHz 13321.428571KHz.pcm/frames_parser.log \
    datasets/drones/xiaomi_mi_drone_4k/13_40_03 5765.117978MHz 13321.428571KHz.pcm/frames_phy.log \
    datasets/drones/xiaomi_mi_drone_4k/13_40_03 5765.117978MHz 13321.428571KHz.pcm/func.log \
    datasets/non-drones/droidcam_voip/frames.log \
    datasets/non-drones/droidcam_voip/frames.pcap \
    datasets/non-drones/droidcam_voip/frames_parser.log \
    datasets/non-drones/droidcam_voip/frames_phy.log \
    datasets/non-drones/droidcam_voip/func.log \
    datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/frames.log \
    datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/frames.pcap \
    datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/frames_parser.log \
    datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/frames_phy.log \
    datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/func.log \
    datasets/non-drones/test_download_app_from_appstore_with_terminations_and_pause/readme.txt \
    datasets/non-drones/test_pdf/frames.log \
    datasets/non-drones/test_pdf/frames.pcap \
    datasets/non-drones/test_pdf/frames_parser.log \
    datasets/non-drones/test_pdf/frames_phy.log \
    datasets/non-drones/test_pdf/func.log \
    datasets/non-drones/test_pdf/readme.txt \
    datasets/non-drones/test_ping/frames.log \
    datasets/non-drones/test_ping/frames.pcap \
    datasets/non-drones/test_ping/frames_parser.log \
    datasets/non-drones/test_ping/frames_phy.log \
    datasets/non-drones/test_ping/func.log \
    datasets/non-drones/test_ping/readme.txt \
    datasets/non-drones/test_twitch/frames.log \
    datasets/non-drones/test_twitch/frames.pcap \
    datasets/non-drones/test_twitch/frames_parser.log \
    datasets/non-drones/test_twitch/frames_phy.log \
    datasets/non-drones/test_twitch/func.log \
    datasets/non-drones/test_twitch/readme.txt \
    datasets/non-drones/test_yandex_maps/frames.log \
    datasets/non-drones/test_yandex_maps/frames.pcap \
    datasets/non-drones/test_yandex_maps/frames_parser.log \
    datasets/non-drones/test_yandex_maps/frames_phy.log \
    datasets/non-drones/test_yandex_maps/func.log \
    datasets/non-drones/test_yandex_maps/readme.txt \
    datasets/non-drones/test_youtube/frames.log \
    datasets/non-drones/test_youtube/frames.pcap \
    datasets/non-drones/test_youtube/frames_parser.log \
    datasets/non-drones/test_youtube/frames_phy.log \
    datasets/non-drones/test_youtube/func.log \
    datasets/non-drones/test_youtube/readme.txt \
    datasets/train/func.log
