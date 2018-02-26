cat <<EOF >search_engine.ctpl.h
// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: tianmo@baidu.com (Mo Tian)
//
EOF
../../../../../../../../third-64/ctemplate/bin/template-converter search_engine_ctpl search_engine.ctpl >>search_engine.ctpl.h
# Style.
sed -i 's#SEARCH_ENGINE_CTPL_H_#UNISE_FRONTEND_CTPL_SEARCH_ENGINE_CTPL_H_#' search_engine.ctpl.h
sed -i 's#/\*# //#' search_engine.ctpl.h
sed -i 's# \*/##' search_engine.ctpl.h
sed -i 's#../../../../../../../../third-64/ctemplate/bin/##' search_engine.ctpl.h
sed -i 's#search_engine_ctpl (#search_engine_ctpl(#' search_engine.ctpl.h
sed -i 's#^const string#const std::string#' search_engine.ctpl.h
