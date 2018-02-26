cat <<EOF >binlog.ctpl.h
// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: tianmo@baidu.com (Mo Tian)
//
EOF
../../../../../../../../third-64/ctemplate/bin/template-converter binlog_ctpl binlog.ctpl>>binlog.ctpl.h
# Style.
sed -i 's#DEFAULT_CTPL_H_#UNISE_FRONTEND_CTPL_BINLOG_CTPL_H_#' binlog.ctpl.h
sed -i 's#/\*# //#' binlog.ctpl.h
sed -i 's# \*/##' binlog.ctpl.h
sed -i 's#../../../../../../../../third-64/ctemplate/bin/##' binlog.ctpl.h
sed -i 's#binlog_ctpl (#binlog_ctpl(#' binlog.ctpl.h
sed -i 's#^const string#const std::string#' binlog.ctpl.h
