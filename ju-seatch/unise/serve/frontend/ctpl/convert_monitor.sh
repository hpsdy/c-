cat <<EOF >monitor.ctpl.h
// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: tianmo@baidu.com (Mo Tian)
//
EOF
../../../../../../../../third-64/ctemplate/bin/template-converter monitor_ctpl monitor.ctpl >>monitor.ctpl.h
# Style.
sed -i 's#MONITOR_CTPL_H_#UNISE_FRONTEND_CTPL_MONITOR_CTPL_H_#' monitor.ctpl.h
sed -i 's#/\*# //#' monitor.ctpl.h
sed -i 's# \*/##' monitor.ctpl.h
sed -i 's#../../../../../../../../third-64/ctemplate/bin/##' monitor.ctpl.h
sed -i 's#monitor_ctpl (#monitor_ctpl(#' monitor.ctpl.h
sed -i 's#^const string#const std::string#' monitor.ctpl.h
