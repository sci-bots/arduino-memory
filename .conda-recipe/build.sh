mkdir -p "${PREFIX}"/include/Arduino
cp -ra "${SRC_DIR}"/include/Arduino/Memory "${PREFIX}"/include/Arduino/Memory
rc=$?; if [[ $rc != 0  ]]; then exit $rc; fi
