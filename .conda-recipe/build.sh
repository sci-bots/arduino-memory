mkdir -p "${PREFIX}"
cp -ra "${SRC_DIR}" "${PREFIX}"
rc=$?; if [[ $rc != 0  ]]; then exit $rc; fi
