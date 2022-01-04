# Makefile to build all programs in all subdirectories

DIRS = 	fifo \
		message_queue \
		socket
BUILD_DIRS = ${DIRS}

make: 	
	@ echo ${BUILD_DIRS}
	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE}) ; \
		if test $$? -ne 0; then break; fi; done

clean:

	@ for dir in ${BUILD_DIRS}; do (cd $${dir}; ${MAKE} clean) ; done
