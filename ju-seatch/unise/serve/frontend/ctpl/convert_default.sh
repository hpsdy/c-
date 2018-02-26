cat <<EOF >default.ctpl.h
// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: tianmo@baidu.com (Mo Tian)
//
EOF
../../../../../../../../third-64/ctemplate/bin/template-converter default_ctpl default.ctpl>>default.ctpl.h
# Style.
sed -i 's#DEFAULT_CTPL_H_#UNISE_FRONTEND_CTPL_DEFAULT_CTPL_H_#' default.ctpl.h
sed -i 's#/\*# //#' default.ctpl.h
sed -i 's# \*/##' default.ctpl.h
sed -i 's#../../../../../../../../third-64/ctemplate/bin/##' default.ctpl.h
sed -i 's#default_ctpl (#default_ctpl(#' default.ctpl.h
sed -i 's#^const string#const std::string#' default.ctpl.h
