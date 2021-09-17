FROM rootproject/root-conda

ARG GEANT=http://cern.ch/geant4-data/releases/geant4.10.06.p01.tar.gz

RUN conda install -y make cmake=3.11.1 \
    && wget -q $GEANT \
    && tar -xzf geant4.10.06.p01.tar.gz \
    && mkdir -p geant4-build && cd geant4-build \
    && cmake -DGEANT4_USE_SYSTEM_EXPAT=OFF \
             -DGEANT4_INSTALL_DATA=ON \
	     ../geant4.10.06.p01 \
    && make -j 4 \
    && make install \
    && cd /usr/local/bin \
    && . geant4.sh \
    && env \
    && cd / \
    && rm geant4.10.06.p01.tar.gz \
    && rm -r geant4-build
