#!/bin/sh

VERSION_FILE=$1
OUTPUT_FILE=$2

if test -z "$VERSION_FILE";then
    VERSION_FILE="VERSION"
fi

if test -z "$OUTPUT_FILE";then
    OUTPUT_FILE="libmapi/version.h"
fi

OPENCHANGE_VERSION_STRING=$3
SOURCE_DIR=$4

OPENCHANGE_MAJOR_RELEASE=`echo ${OPENCHANGE_VERSION_STRING} | cut -d. -f1`
OPENCHANGE_MINOR_RELEASE=`echo ${OPENCHANGE_VERSION_STRING} | cut -d. -f2`

OPENCHANGE_VERSION_IS_GIT_SNAPSHOT=`sed -n 's/^OPENCHANGE_VERSION_IS_GIT_SNAPSHOT=//p' $SOURCE_DIR$VERSION_FILE`
OPENCHANGE_VERSION_RELEASE_NICKNAME=`sed -n 's/^OPENCHANGE_VERSION_RELEASE_NICKNAME=//p' $SOURCE_DIR$VERSION_FILE`
OPENCHANGE_VERSION_RELEASE_NUMBER=`sed -n 's/^OPENCHANGE_VERSION_RELEASE_NUMBER=//p' $SOURCE_DIR$VERSION_FILE`

TMPFILE=`mktemp`

echo "/* Autogenerated by script/mkversion.h */" >> $TMPFILE
echo "#define OPENCHANGE_MAJOR_RELEASE ${OPENCHANGE_MAJOR_RELEASE}" >> $TMPFILE
echo "#define OPENCHANGE_MINOR_RELEASE ${OPENCHANGE_MINOR_RELEASE}" >> $TMPFILE

#
# GIT revision number
#
if test x"${OPENCHANGE_VERSION_IS_GIT_SNAPSHOT}" = x"yes";then
    _SAVE_LANG=${LANG}
    LANG=""
    HAVEVER="no"

    if test x"${HAVEVER}" != x"yes";then
        HAVEGIT="no"
        GIT_INFO=`git rev-parse --short HEAD`
        if test -n "$GIT_INFO"; then
            HAVEGIT="yes"
            HAVEVER="yes"
        fi
    fi

    if test x"${HAVEGIT}" = x"yes";then
        OPENCHANGE_VERSION_STRING="${OPENCHANGE_VERSION_STRING}-GIT-build-${GIT_INFO}"
        echo "#define OPENCHANGE_VERSION_GIT_REVISION ${GIT_INFO}" >> $TMPFILE
    fi

    LANG=${_SAVE_LANG}
fi

if test -z "${OPENCHANGE_VERSION_RELEASE_NUMBER}";then
    echo "#define OPENCHANGE_VERSION_OFFICIAL_STRING \"${OPENCHANGE_VERSION_STRING}\"" >> $TMPFILE
else
    OPENCHANGE_VERSION_STRING="${OPENCHANGE_VERSION_RELEASE_NUMBER}"
    echo "#define OPENCHANGE_VERSION_OFFICIAL_STRING \"${OPENCHANGE_VERSION_RELEASE_NUMBER}\"" >> $TMPFILE
fi

##
## Add a release nickname
##
if test -n "${OPENCHANGE_VERSION_RELEASE_NICKNAME}";then
    echo "#define OPENCHANGE_VERSION_RELEASE_NICKNAME ${OPENCHANGE_VERSION_RELEASE_NICKNAME}" >> $TMPFILE
    if test x"${HAVEGIT}" = x"yes";then
	OPENCHANGE_VERSION_STRING="${OPENCHANGE_VERSION_STRING}-GIT-${GIT_INFO} (${OPENCHANGE_VERSION_RELEASE_NICKNAME})"
    else
	OPENCHANGE_VERSION_STRING="${OPENCHANGE_VERSION_STRING} (${OPENCHANGE_VERSION_RELEASE_NICKNAME})"
    fi
fi

echo "#define OPENCHANGE_VERSION_STRING \"${OPENCHANGE_VERSION_STRING}\"" >> $TMPFILE

##
## Add some System related information (useful for debug and report)
##
echo "" >> $TMPFILE
echo "/* System related information */" >> $TMPFILE

OPENCHANGE_SYS_KERNEL_NAME=`uname -s`
OPENCHANGE_SYS_KERNEL_RELEASE=`uname -r`
OPENCHANGE_SYS_PROCESSOR=`uname -p`

echo "#define OPENCHANGE_SYS_KERNEL_NAME \"${OPENCHANGE_SYS_KERNEL_NAME}\"" >> $TMPFILE
echo "#define OPENCHANGE_SYS_KERNEL_RELEASE \"${OPENCHANGE_SYS_KERNEL_RELEASE}\"" >> $TMPFILE
echo "#define OPENCHANGE_SYS_PROCESSOR \"${OPENCHANGE_SYS_PROCESSOR}\"" >> $TMPFILE

mv "$TMPFILE" "$OUTPUT_FILE"

echo "$0: '$OUTPUT_FILE' created for OpenChange libmapi(\"${OPENCHANGE_VERSION_STRING}\")"

exit 0
