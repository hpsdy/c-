cat <<EOF >index.ctpl.h
// Copyright 2015 Baidu.com  All Rights Reserved.
// Author: wangguangyuan@baidu.com (Guangyuan Wang)
//
EOF
../../../../../../../../third-64/ctemplate/bin/template-converter index_ctpl index.ctpl>>index.ctpl.h
# Style.
sed -i 's#DEFAULT_CTPL_H_#UNISE_FRONTEND_CTPL_INDEX_CTPL_H_#' index.ctpl.h
sed -i 's#/\*# //#' index.ctpl.h
sed -i 's# \*/##' index.ctpl.h
sed -i 's#../../../../../../../../third-64/ctemplate/bin/##' index.ctpl.h
sed -i 's#index_ctpl (#index_ctpl(#' index.ctpl.h
sed -i 's#^const string#const std::string#' index.ctpl.h
