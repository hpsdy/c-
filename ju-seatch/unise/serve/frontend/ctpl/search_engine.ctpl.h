// Copyright 2013 Baidu.com  All Rights Reserved.
// Author: tianmo@baidu.com (Mo Tian)
//
// This file automatically generated by template-converter:
//    template-converter search_engine_ctpl search_engine.ctpl
//
// DO NOT EDIT!

#ifndef UNISE_FRONTEND_CTPL_SEARCH_ENGINE_CTPL_H_
#define UNISE_FRONTEND_CTPL_SEARCH_ENGINE_CTPL_H_

#include <string>

const std::string search_engine_ctpl(
"<html lang=\"en\">\n"
"  <head>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
"    <link href=\"http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css\" rel=\"stylesheet\">\n"
"    <title>Unise Frontend</title>\n"
"    {{#SCRIPT}}\n"
"    {{/SCRIPT}}\n"
"    <style type=\"text/css\">\n"
"    .pre {\n"
"        white-space: pre-wrap\n"
"    }\n"
"    EM {\n"
"        COLOR: red; font-style:normal\n"
"    }\n"
"    body {\n"
"        padding-top: 70px;\n"
"    }\n"
"    .foot {\n"
"        height:50px;\n"
"        width:100%;\n"
"        background:#EEEEEE;\n"
"        color:#000;\n"
"        font-size:14px;\n"
"        text-align:center;\n"
"    }\n"
"    a:hover {\n"
"        text-decoration:none;\n"
"    }\n"
"    </style>\n"
"  </head>\n"
"\n"
"  <body>\n"
"     <div class=\"navbar navbar-default navbar-fixed-top\" role=\"navigation\" style=\"background-color:#01184A;\">\n"
"      <div class=\"container\">\n"
"        <div class=\"navbar-header\">\n"
"            <span class=\"navbar-brand\" style=\"color: #FFF;font-size:27px;font-weight:bold;\">UniSE Frontend</span>\n"
"        </div>\n"
"        <div class=\"navbar-collapse collapse\">\n"
"          <ul class=\"nav navbar-nav navbar-right\">\n"
"            {{#ONE_PAGE_INFO_LEAD}}\n"
"            {{PAGE_LEAD}}\n"
"            {{/ONE_PAGE_INFO_LEAD}}\n"
"          </ul>\n"
"      </div>\n"
"      </div>\n"
"    </div>\n"
"    <div class=\"container\">\n"
"       <div class=\"jumbotron\">\n"
"       <span style=\"font-size:13px;color:#01184A;font-weight:bold;\">&gt;&gt;SearchEngineProcessor</span><br>\n"
"        {{#INPUT}}\n"
"        <div class='input_box' style=\"font-size:14px;background-color:#F1F9F7;\">      \n"
"        <form method='GET' action='/search' enctype='enctype=application/x-www-form-urlencoded'>\n"
"         <table border=0 style=\"font-size:14px;\">\n"
"            <tr>\n"
"                <td>\n"
"                    <table borer=0 style=\"font-size:14px;\">\n"
"                      <tr>\n"
"                        <td>Query Tree:</td>\n"
"                        <td><textarea style='max-width:600px;max-height:300px' name='query' cols=46 rows=3>{{LAST_QUERY}}</textarea></td>\n"
"                        <td>&nbsp;&nbsp;&nbsp;NumOfResult:&nbsp;<input name='num_results' value='{{LAST_NUM_RESULTS}}' style='height:30px;width:60px;'/></td>\n"
"                        <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>\n"
"                        <td><input type='submit' value='search' style='height:30px;width:70px;background-color:#01184A;color:#FFF;border:0px'/></td>\n"
"                      </tr>\n"
"                    </table>\n"
"                </td>\n"
"            </tr>\n"
"         </table>\n"
"        <div id='idtest'>\n"
"        <table border=0 style='font-size:14px;'>\n"
"          <tr align='center'>\n"
"            <td>RawQuery:</td>\n"
"            <td><input name='raw_query' value='{{LAST_RAW_QUERY}}'style='height:30px;width:220px'/></td>\n"
"          </tr>\n"
"          <tr align='center'>\n"
"            <td>StartResult:</td>\n"
"            <td><input name='start_result' value='{{LAST_START_RESULT}}'style='height:30px;width:120px'/></td>\n"
"            <td>&nbsp;&nbsp;StartDocid:</td>\n"
"            <td><input name='start_docid' value='{{LAST_START_DOCID}}' style='height:30px;width:80px;'/></td>\n"
"            <td>&nbsp;&nbsp;RetrieveTimeOut:</td>\n"
"            <td><input name='retrieve_timeout' value='{{LAST_RETRIEVE_TIMEOUT}}' style='height:30px;width:100px;'/></td>\n"
"            <td>&nbsp;&nbsp;RetrieveDepth:</td>\n"
"            <td><input name='retrieve_depth' value='{{LAST_RETRIEVE_DEPTH}}' style='height:30px;width:140px;'/></td>\n"
"          </tr>\n"
"          <tr align='center'>\n"
"            <td>RecallDocs:</td>\n"
"            <td><input name='recall_docs' value='{{LAST_RECALL_DOCS}}' style='height:30px;width:120px;'/></td>\n"
"            <td>&nbsp;&nbsp;SessionID:</td>\n"
"            <td><input name='session_id' value='{{LAST_SESSION_ID}}' style='height:30px;width:80px;'/></td>\n"
"            <td>&nbsp;&nbsp;BusinessID:</td>\n"
"            <td><input name='business_id' value='{{LAST_BUSINESS_ID}}' style='height:30px;width:100px;'/></td>\n"
"            <td>&nbsp;&nbsp;RangeRestrictAnno:</td>\n"
"            <td><input name='range_restriction_annotation' value='{{LAST_RANGE_RESTRICTION_ANNOTATION}}' style='height:30px;width:140px;'/></td>\n"
"          </tr>\n"
"          <tr align='center'>\n"
"            <td>SortParams:</td>\n"
"            <td><input name='sort_params' value='{{LAST_SORT_PARAMS}}' style='height:30px;width:120px;' /></td>\n"
"            <td>&nbsp;&nbsp;SampleID:</td>\n"
"            <td><input name='sample_id' value='{{LAST_SAMPLE_ID}}' style='height:30px;width:80px;'/></td>\n"
"            <td>&nbsp;&nbsp;RangeMin:</td>\n"
"            <td><input name='range_min' value='{{LAST_RANGE_MIN}}' style='height:30px;width:100px;'/></td>\n"
"            <td>&nbsp;&nbsp;RangeMax:</td>\n"
"            <td><input name='range_max' value='{{LAST_RANGE_MAX}}' style='height:30px;width:140px;'/></td/>\n"
"          </tr>\n"
"          <tr><td colspan=8>\n"
"            <table borer=0 style='font-size:14px;'>\n"
"                <tr>\n"
"                  <td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;Experiments:<br>(format:k1:v1,k2:v2,k3:v3)</td>\n"
"                  <td><textarea name='experiments' cols='57' rows=3 style='max-width:600px;max-height:300px'>{{LAST_EXPERIMENTS}}</textarea></td>\n"
"                </tr>\n"
"            </table>\n"
"         </td></tr>\n"
"        </table>        \n"
"        </div>\n"
"       </form>\n"
"      </div>\n"
"    {{/INPUT}}\n"
"  <hr size=\"1\" noshade=\"noshade\" style=\"border:1px #cccccc dotted;\">\n"
"  {{#RESULT_OUTPUT}}\n"
"  <div>\n"
"   <span style=\"font-size:13px;color:#01184A;font-weight:bold;\">&gt;&gt;SearchResultInfo</span><br>     \n"
"    <div class='top_info' style=\"font-size:14px;background-color:#CCFFCC;line-height:40px;\">\n"
"      NumResults:{{NUM_RESULTS}}&nbsp;\n"
"      ExactNumResults:{{EXACT_NUM_RESULTS}}&nbsp;\n"
"      EstimatedNumResults:{{EST_NUM_RESULTS}}&nbsp;\n"
"      DocsRetrieved:{{DOCS_RETRIEVED}}&nbsp;\n"
"      DocsRecalled:{{DOCS_RECALLED}}&nbsp;\n"
"      SearchTime:{{SEARCH_TIME}}ms&nbsp;\n"
"      StatusCode:{{STATUS_CODE}}&nbsp;\n"
"      StatusMsg:{{STATUS_MSG}}&nbsp;\n"
"      RpcInfo:{{RPC_INFO}}\n"
"      <br>\n"
"      <table border=0 style=\"font-size:14px;\"><tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td><td><div style=\"font-size:14px;line-height:30px;\">\n"
"          {{#SE_PLUGIN_RESPONSE}}\n"
"              <div style=\"font-size:14px;line-height:30px;\">\n"
"              {{SE_PLUGIN_NAME}}&nbsp;\n"
"              enable[{{SE_PLUGIN_ENABLE}}]&nbsp;{{SE_PLUGIN_INFORMATION}}<br>\n"
"              </div>\n"
"          {{/SE_PLUGIN_RESPONSE}}\n"
"          {{#ENGINE_UNIT_RESPONSE}}\n"
"            From:{{ENGINE_UNIT_NAME}}&nbsp;\n"
"            Type:{{ENGINE_UNIT_TYPE}}&nbsp;\n"
"            NumResults:{{ENGINE_UNIT_NUM_RESULTS}}&nbsp;\n"
"            EstimatedNumResults:{{ENGINE_UNIT_EST_NUM_RESULTS}}&nbsp;\n"
"            DocsRetrieved:{{ENGINE_UNIT_DOCS_RETRIEVED}}&nbsp;\n"
"            DocsRecalled:{{ENGINE_UNIT_DOCS_RECALLED}}&nbsp;\n"
"            SearchTime:{{ENGINE_UNIT_SEARCH_TIME}}ms&nbsp;\n"
"            <br>\n"
"              <div style=\"font-size:14px;line-height:30px;\">\n"
"              {{#PLUGIN_RESPONSE}}\n"
"                {{PLUGIN_NAME}}&nbsp;\n"
"                enable[{{PLUGIN_ENABLE}}]&nbsp;{{PLUGIN_INFORMATION}}<br>\n"
"              {{/PLUGIN_RESPONSE}}\n"
"              </div>\n"
"          {{/ENGINE_UNIT_RESPONSE}}\n"
"      </div></td></tr></table>\n"
"    </div>\n"
"   <hr size=\"1\" noshade=\"noshade\" style=\"border:1px #cccccc dotted;\">\n"
"   <span style=\"font-size:13px;color:#01184A;font-weight:bold;\">&gt;&gt;SearchResult</span><br>\n"
"   {{#ONE_RESULT}}\n"
"     <div style=\"line-height:8px;\">&nbsp;</div>\n"
"     <table ><tr><td>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;</td>     \n"
"      <td align='middle' width='40px'><font size=4><b>{{RESULT_ID}}</b></font></td>\n"
"      <td align='middle' width='80px'><font size=3><b>{{RESULT_DOCID}}</b></font></td>\n"
"      <td align='middle' width='40px'><font size=2 color='red'><b>{{RESULT_SCORE}}</b></font></td>\n"
"      <td>\n"
"       <div style=\"font-size:15px;word-break:break-all;word-wrap:break-word;line-height:22px;\">{{RESULT_SNIPPET}}</div>\n"
"      </td>\n"
"     </tr></table>\n"
"   {{/ONE_RESULT}}\n"
"  {{/RESULT_OUTPUT}}\n"
"  </div>\n"
"    <hr size=\"1\" noshade=\"noshade\" style=\"border:1px #cccccc dotted;\">\n"
"    <div class=\"foot\">Any Question, Contact to unise@baidu.com<br/>2015-04-17</div>\n"
"  </div>\n"
"  </div>\n"
"\n"
" </body>\n"
"</html>\n"
);

#endif  // UNISE_FRONTEND_CTPL_SEARCH_ENGINE_CTPL_H_
