// Copyright 2014 Baidu.com  All Rights Reserved.
// Author: tianmo@baidu.com (Mo Tian)
//
// This file automatically generated by template-converter:
//    template-converter binlog_ctpl binlog.ctpl
//
// DO NOT EDIT!

#ifndef BINLOG_CTPL_H_
#define BINLOG_CTPL_H_

#include <string>

const std::string binlog_ctpl(
"<html lang=\"en\">\n"
"  <head>\n"
"    <meta charset=\"utf-8\">\n"
"    <meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">\n"
"    <meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">\n"
"    <title>Unise Frontend</title>\n"
"    <link href=\"http://libs.baidu.com/bootstrap/3.0.3/css/bootstrap.min.css\" rel=\"stylesheet\">\n"
"    <script src=\"http://libs.baidu.com/jquery/1.9.0/jquery.js\"></script>\n"
"    <script src=\"http://libs.baidu.com/bootstrap/3.0.3/js/bootstrap.js\"></script>\n"
"    <style type=\"text/css\">\n"
"    * {\n"
"        margin:0px;\n"
"        padding:0px;\n"
"    }\n"
"    .head {\n"
"        height:50px;\n"
"        width:100%;\n"
"        background:#6CF;\n"
"        color:#000;\n"
"    }\n"
"    .foot {\n"
"        height:50px;\n"
"        width:100%;\n"
"        background:#EEEEEE;\n"
"        color:#000;\n"
"        font-size:14px;\n"
"        text-align:center;\n"
"    }\n"
"    .output_area00{  \n"
"        width:100%;\n"
"        overflow:auto;  \n"
"        word-break:break-all; \n"
"    }\n"
"    .input_area00{  \n"
"        width:100%;\n"
"        overflow:auto;  \n"
"        word-break:break-all; \n"
"    }\n"
"    body {\n"
"        padding-top: 70px;\n"
"    }\n"
"    </style>\n"
"  </head>\n"
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
"\n"
"   {{#INPUT}}\n"
"   {{#RESULT_OUTPUT}}\n"
"    <div class=\"container\">\n"
"       <div class=\"jumbotron\" style=\"height:700px\">\n"
"           <span style=\"font-size:13px;color:#01184A;font-weight:bold;\">&gt;&gt;BinlogProcessor&gt;&gt;base64 convert to Protobuf TextFormat</span><br>\n"
"           <hr size=\"1\" noshade=\"noshade\" style=\"border:1px #cccccc dotted;\">\n"
"               <table><tr><td>\n"
"                <div class=\"col-md-4\">\n"
"                    <ul class=\"nav nav-tabs nav-justified\" role=\"tablist\">\n"
"                      <li name='req_name' id='req_check_box' class=\"active\"><a id=\"monitor_tab\" href=\"#monitor\" role=\"tab\" data-toggle=\"tab\">GeneralSearchRequest</a></li>\n"
"                      <li name='rsp_name' id='rsp_check_box'><a id=\"manage_tab\" href=\"#manage\" role=\"tab\" data-toggle=\"tab\">GeneralSearchResponse</a></li>\n"
"                       </ul>\n"
"                    <div style=\"height:5px;\"></div>\n"
"                    <div class=\"tab-content\">\n"
"                    <!--- 111 --->\n"
"                      <div class=\"tab-pane active\" name='monitor' id=\"monitor\" style=\"width:980px\"> \n"
"                       <form method='GET' name='request_form' action='/binlog' enctype='enctype=application/x-www-form-urlencoded' onsubmit=\"return request_submit()\">\n"
"                        <table width='980px' align='center' border='0'>\n"
"                            <tr width='100%' height='60'><td colspan='3' align='right'>\n"
"                                <input type='submit' value='ConvertRequest' style='font-size:14px;height:40px;width:140px;background-color:#01184A;color:#FFF;border:0px'/><br>\n"
"                            </td></tr>\n"
"                            <tr><td width='50%'>\n"
"                               <textarea style='font-size:14px;max-width:600px;max-height:450px' class='input_area00' name='request_base64' rows='20' onpropertychange=\"this.style.posHeight=this.scrollHeight\">{{LAST_REQUEST_BASE64}}</textarea>\n"
"                            </td><td>&nbsp;<span style=\"font-size:14px;color:#01184A;font-weight:bold;\">=></span>&nbsp;</td><td width='50%'>\n"
"                               <textarea style=\"font-size:14px;\" class='output_area00' name='request_text' rows='20' onpropertychange=\"this.style.posHeight=this.scrollHeight\">{{REQUEST_TEXT}}</textarea>\n"
"                            </td></tr>\n"
"                        </table>\n"
"                       </form>\n"
"                       </div>\n"
"                      <!--- 222 --->\n"
"                      <div class=\"tab-pane\" name='manage' id=\"manage\" style=\"width:980px\">\n"
"                       <form method='GET' name='response_form' action='/binlog' enctype='enctype=application/x-www-form-urlencoded' onsubmit=\"return response_submit()\">\n"
"                       <table style=\"width:980px\" align='center' border='0'>\n"
"                            <tr width='100%' height='60'><td colspan='3' align='right'>\n"
"                                <input type='submit' id='response_button' value='ConvertResponse' style='font-size:14px;height:40px;width:140px;background-color:#01184A;color:#FFF;border:0px'/><br>\n"
"                            </td></tr>\n"
"                            <tr><td width='50%'>\n"
"                               <textarea style=\"font-size:14px;max-width:600px;max-height:450px\" class='input_area00' name='response_base64' id='response_base64' rows='20' onpropertychange=\"this.style.posHeight=this.scrollHeight\">{{LAST_RESPONSE_BASE64}}</textarea>\n"
"                            </td><td>&nbsp;<span style=\"font-size:14px;color:#01184A;font-weight:bold;\">=></span>&nbsp;</td><td width='50%'>\n"
"                               <textarea style=\"font-size:14px;\" class='output_area00' name='response_text' id='response_text' rows='20' onpropertychange=\"this.style.posHeight=this.scrollHeight\">{{RESPONSE_TEXT}}</textarea>\n"
"                            </td></tr>\n"
"                        </table>\n"
"                      </form>\n"
"                      </div>\n"
"                   </div>\n"
"                </div>\n"
"           </td></tr><tr><td><br>\n"
"           </td></tr></table>\n"
"        <div class=\"foot\">Any Question, Contact to vsce@baidu.com<br/>2014-09-17</div>\n"
"        </div>\n"
"    </div>\n"
"\n"
"   {{/RESULT_OUTPUT}}\n"
"   {{/INPUT}}\n"
"\n"
"  {{#SCRIPT}}\n"
"  {{/SCRIPT}}\n"
"  <script type=\"text/javascript\">\n"
"    function request_submit() {\n"
"        if (request_form.request_base64.value == '') {\n"
"            alert('request base64 null.');\n"
"            return false;\n"
"        }\n"
"        return true;\n"
"    }\n"
"    function response_submit() {\n"
"        if (response_form.response_base64.value == '') {\n"
"            alert('response base64 null.');\n"
"            return false;\n"
"        }\n"
"        return true;\n"
"    }\n"
"\n"
"   var cparam = get_param();\n"
"   for (j = 0; j < cparam.length; ++ j) {\n"
"     if (cparam[j] == 'response_base64') {\n"
"       var a = document.getElementsByTagName('div');\n"
"       for (var i = 0; i < a.length; ++ i) {\n"
"           if (a[i].className == 'tab-pane active') {\n"
"               a[i].className = 'tab-pane';\n"
"           } else if (a[i].className == 'tab-pane') {\n"
"               a[i].className = 'tab-pane active';\n"
"           } \n"
"       }   \n"
"       var obj = document.getElementById('req_check_box');\n"
"       if (obj.className == 'active') {\n"
"           obj.className  = '';\n"
"           document.getElementById('rsp_check_box').className = 'active';\n"
"       }       \n"
"       break;\n"
"      }\n"
"    }\n"
"    function get_param(){\n"
"        querystr = window.location.href.split('?');\n"
"        if(querystr[1]){\n"
"            kv = querystr[1].split('&');\n"
"            var keys = [];\n"
"            for(i = 0; i < kv.length; i++){\n"
"                tmp_arr = kv[i].split('=');\n"
"                keys.push(tmp_arr[0]);\n"
"            }\n"
"        }\n"
"        return keys;\n"
"    }\n"
"  </script>\n"
" </body>\n"
"</html>\n"
);

#endif  // BINLOG_CTPL_H_
