TARGET=$@
Q_PLACEHOLDER = src/question_placeholder.h
SLAVE_IMAGE = srzzumix/googletest
SLAVE_TAG = latest
SLAVE_WORK_DIR = /leetcode
BUILT_EXE = ${SLAVE_WORK_DIR}/build/main.out
BUILD_CMD = g++ ${SLAVE_WORK_DIR}/src/main.cpp -o ${BUILT_EXE}  \
		-std=c++17 -lgtest -lpthread -lgmock
DOCKER_BUILDER_MOUNT="$(PWD):/leetcode"
DOCKER_RUN= docker run --rm=true --privileged --init \
	-v $(DOCKER_BUILDER_MOUNT) \
	$(SLAVE_IMAGE):$(SLAVE_TAG) \
	bash -c "$(BUILD_CMD) && ${BUILT_EXE}"

%::
	@echo build $@ ...
	@[ -d build ] || mkdir build
	@cp -f src/${TARGET}.h ${Q_PLACEHOLDER}
	@${DOCKER_RUN}
	@rm ${Q_PLACEHOLDER}

