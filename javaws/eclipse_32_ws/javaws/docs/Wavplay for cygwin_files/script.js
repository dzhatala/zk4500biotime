(function(factory){if(typeof define==='function'&&define.amd){define(['jquery'],factory);}else{factory(jQuery);}}(function($){$.timeago=function(timestamp){if(timestamp instanceof Date){return inWords(timestamp);}else if(typeof timestamp==="string"){return inWords($.timeago.parse(timestamp));}else if(typeof timestamp==="number"){return inWords(new Date(timestamp));}else{return inWords($.timeago.datetime(timestamp));}};var $t=$.timeago;$.extend($.timeago,{settings:{refreshMillis:60000,allowPast:true,allowFuture:false,localeTitle:false,cutoff:0,strings:{prefixAgo:null,prefixFromNow:null,suffixAgo:"ago",suffixFromNow:"from now",inPast:'any moment now',seconds:"less than a minute",minute:"about a minute",minutes:"%d minutes",hour:"about an hour",hours:"about %d hours",day:"a day",days:"%d days",month:"about a month",months:"%d months",year:"about a year",years:"%d years",wordSeparator:" ",numbers:[]}},inWords:function(distanceMillis){if(!this.settings.allowPast&&!this.settings.allowFuture){throw'timeago allowPast and allowFuture settings can not both be set to false.';}
var $l=this.settings.strings;var prefix=$l.prefixAgo;var suffix=$l.suffixAgo;if(this.settings.allowFuture){if(distanceMillis<0){prefix=$l.prefixFromNow;suffix=$l.suffixFromNow;}}
if(!this.settings.allowPast&&distanceMillis>=0){return this.settings.strings.inPast;}
var seconds=Math.abs(distanceMillis)/ 1000;var minutes=seconds / 60;var hours=minutes / 60;var days=hours / 24;var years=days / 365;function substitute(stringOrFunction,number){var string=$.isFunction(stringOrFunction)?stringOrFunction(number,distanceMillis):stringOrFunction;var value=($l.numbers&&$l.numbers[number])||number;return string.replace(/%d/i,value);}
var words=seconds<45&&substitute($l.seconds,Math.round(seconds))||seconds<90&&substitute($l.minute,1)||minutes<45&&substitute($l.minutes,Math.round(minutes))||minutes<90&&substitute($l.hour,1)||hours<24&&substitute($l.hours,Math.round(hours))||hours<42&&substitute($l.day,1)||days<30&&substitute($l.days,Math.round(days))||days<45&&substitute($l.month,1)||days<365&&substitute($l.months,Math.round(days / 30))||years<1.5&&substitute($l.year,1)||substitute($l.years,Math.round(years));var separator=$l.wordSeparator||"";if($l.wordSeparator===undefined){separator=" ";}
return $.trim([prefix,words,suffix].join(separator));},parse:function(iso8601){var s=$.trim(iso8601);s=s.replace(/\.\d+/,"");s=s.replace(/-/,"/").replace(/-/,"/");s=s.replace(/T/," ").replace(/Z/," UTC");s=s.replace(/([\+\-]\d\d)\:?(\d\d)/," $1$2");s=s.replace(/([\+\-]\d\d)$/," $100");return new Date(s);},datetime:function(elem){var iso8601=$t.isTime(elem)?$(elem).attr("datetime"):$(elem).attr("title");return $t.parse(iso8601);},isTime:function(elem){return $(elem).get(0).tagName.toLowerCase()==="time";}});var functions={init:function(){var refresh_el=$.proxy(refresh,this);refresh_el();var $s=$t.settings;if($s.refreshMillis>0){this._timeagoInterval=setInterval(refresh_el,$s.refreshMillis);}},update:function(time){var parsedTime=$t.parse(time);$(this).data('timeago',{datetime:parsedTime});if($t.settings.localeTitle)$(this).attr("title",parsedTime.toLocaleString());refresh.apply(this);},updateFromDOM:function(){$(this).data('timeago',{datetime:$t.parse($t.isTime(this)?$(this).attr("datetime"):$(this).attr("title"))});refresh.apply(this);},dispose:function(){if(this._timeagoInterval){window.clearInterval(this._timeagoInterval);this._timeagoInterval=null;}}};$.fn.timeago=function(action,options){var fn=action?functions[action]:functions.init;if(!fn){throw new Error("Unknown function name '"+action+"' for timeago");}
this.each(function(){fn.call(this,options);});return this;};function refresh(){var data=prepareData(this);var $s=$t.settings;if(!isNaN(data.datetime)){if($s.cutoff==0||Math.abs(distance(data.datetime))<$s.cutoff){$(this).text(inWords(data.datetime));}}
return this;}
function prepareData(element){element=$(element);if(!element.data("timeago")){element.data("timeago",{datetime:$t.datetime(element)});var text=$.trim(element.text());if($t.settings.localeTitle){element.attr("title",element.data('timeago').datetime.toLocaleString());}else if(text.length>0&&!($t.isTime(element)&&element.attr("title"))){element.attr("title",text);}}
return element.data("timeago");}
function inWords(date){return $t.inWords(distance(date));}
function distance(date){return(new Date().getTime()-date.getTime());}
document.createElement("abbr");document.createElement("time");}));!function(e){var t,o={className:"autosizejs",id:"autosizejs",append:"\n",callback:!1,resizeDelay:10,placeholder:!0},i='<textarea tabindex="-1" style="position:absolute; top:-999px; left:0; right:auto; bottom:auto; border:0; padding: 0; -moz-box-sizing:content-box; -webkit-box-sizing:content-box; box-sizing:content-box; word-wrap:break-word; height:0 !important; min-height:0 !important; overflow:hidden; transition:none; -webkit-transition:none; -moz-transition:none;"/>',a=["fontFamily","fontSize","fontWeight","fontStyle","letterSpacing","textTransform","wordSpacing","textIndent","whiteSpace"],n=e(i).data("autosize",!0)[0];n.style.lineHeight="99px","99px"===e(n).css("lineHeight")&&a.push("lineHeight"),n.style.lineHeight="",e.fn.autosize=function(i){return this.length?(i=e.extend({},o,i||{}),n.parentNode!==document.body&&e(document.body).append(n),this.each(function(){function o(){var t,o=window.getComputedStyle?window.getComputedStyle(u,null):null;o?(t=parseFloat(o.width),("border-box"===o.boxSizing||"border-box"===o.webkitBoxSizing||"border-box"===o.mozBoxSizing)&&e.each(["paddingLeft","paddingRight","borderLeftWidth","borderRightWidth"],function(e,i){t-=parseFloat(o[i])})):t=p.width(),n.style.width=Math.max(t,0)+"px"}function s(){var s={};if(t=u,n.className=i.className,n.id=i.id,d=parseFloat(p.css("maxHeight")),e.each(a,function(e,t){s[t]=p.css(t)}),e(n).css(s).attr("wrap",p.attr("wrap")),o(),window.chrome){var r=u.style.width;u.style.width="0px";{u.offsetWidth}u.style.width=r}}function r(){var e,a;t!==u?s():o(),n.value=!u.value&&i.placeholder?p.attr("placeholder")||"":u.value,n.value+=i.append||"",n.style.overflowY=u.style.overflowY,a=parseFloat(u.style.height)||0,n.scrollTop=0,n.scrollTop=9e4,e=n.scrollTop,d&&e>d?(u.style.overflowY="scroll",e=d):(u.style.overflowY="hidden",c>e&&(e=c)),e+=z,Math.abs(a-e)>.01&&(u.style.height=e+"px",n.className=n.className,w&&i.callback.call(u,u),p.trigger("autosize.resized"))}function l(){clearTimeout(h),h=setTimeout(function(){var e=p.width();e!==b&&(b=e,r())},parseInt(i.resizeDelay,10))}var d,c,h,u=this,p=e(u),z=0,w=e.isFunction(i.callback),f={height:u.style.height,overflow:u.style.overflow,overflowY:u.style.overflowY,wordWrap:u.style.wordWrap,resize:u.style.resize},b=p.width(),g=p.css("resize");p.data("autosize")||(p.data("autosize",!0),("border-box"===p.css("box-sizing")||"border-box"===p.css("-moz-box-sizing")||"border-box"===p.css("-webkit-box-sizing"))&&(z=p.outerHeight()-p.height()),c=Math.max(parseFloat(p.css("minHeight"))-z||0,p.height()),p.css({overflow:"hidden",overflowY:"hidden",wordWrap:"break-word"}),"vertical"===g?p.css("resize","none"):"both"===g&&p.css("resize","horizontal"),"onpropertychange"in u?"oninput"in u?p.on("input.autosize keyup.autosize",r):p.on("propertychange.autosize",function(){"value"===event.propertyName&&r()}):p.on("input.autosize",r),i.resizeDelay!==!1&&e(window).on("resize.autosize",l),p.on("autosize.resize",r),p.on("autosize.resizeIncludeStyle",function(){t=null,r()}),p.on("autosize.destroy",function(){t=null,clearTimeout(h),e(window).off("resize",l),p.off("autosize").off(".autosize").css(f).removeData("autosize")}),r())})):this}}(jQuery||$);(function(window){var DetectAdBlock=function(options){this._options={checkOnLoad:false,resetOnEnd:false,loopCheckTime:50,loopMaxNumber:5,baitClass:'pub_300x250 pub_300x250m pub_728x90 text-ad textAd text_ad text_ads text-ads text-ad-links',baitStyle:'width: 1px !important; height: 1px !important; position: absolute !important; left: -10000px !important; top: -1000px !important;'};this._var={version:'3.1.0',bait:null,checking:false,loop:null,loopNumber:0,event:{detected:[],notDetected:[]}};if(options!==undefined){this.setOption(options);}
var self=this;var eventCallback=function(){setTimeout(function(){if(self._options.checkOnLoad===true){if(self._var.bait===null){self._creatBait();}
setTimeout(function(){self.check();},1);}},1);};if(window.addEventListener!==undefined){window.addEventListener('load',eventCallback,false);}else{window.attachEvent('onload',eventCallback);}};DetectAdBlock.prototype._options=null;DetectAdBlock.prototype._var=null;DetectAdBlock.prototype._bait=null;DetectAdBlock.prototype.setOption=function(options,value){if(value!==undefined){var key=options;options={};options[key]=value;}
for(var option in options){this._options[option]=options[option];}
return this;};DetectAdBlock.prototype._creatBait=function(){var bait=document.createElement('div');bait.setAttribute('class',this._options.baitClass);bait.setAttribute('style',this._options.baitStyle);this._var.bait=window.document.body.appendChild(bait);this._var.bait.offsetParent;this._var.bait.offsetHeight;this._var.bait.offsetLeft;this._var.bait.offsetTop;this._var.bait.offsetWidth;this._var.bait.clientHeight;this._var.bait.clientWidth;};DetectAdBlock.prototype._destroyBait=function(){window.document.body.removeChild(this._var.bait);this._var.bait=null;};DetectAdBlock.prototype.check=function(loop){if(loop===undefined){loop=true;}
if(this._var.checking===true){return false;}
this._var.checking=true;if(this._var.bait===null){this._creatBait();}
var self=this;this._var.loopNumber=0;if(loop===true){this._var.loop=setInterval(function(){self._checkBait(loop);},this._options.loopCheckTime);}
this._checkBait(loop);return true;};DetectAdBlock.prototype._checkBait=function(loop){var detected=false;if(this._var.bait===null){this._creatBait();}
if(window.document.body.getAttribute('abp')!==null||this._var.bait.offsetParent===null||this._var.bait.offsetHeight==0||this._var.bait.offsetLeft==0||this._var.bait.offsetTop==0||this._var.bait.offsetWidth==0||this._var.bait.clientHeight==0||this._var.bait.clientWidth==0){detected=true;}
if(window.getComputedStyle!==undefined){var baitTemp=window.getComputedStyle(this._var.bait,null);if(baitTemp.getPropertyValue('display')=='none'||baitTemp.getPropertyValue('visibility')=='hidden'){detected=true;}}
if(loop===true){this._var.loopNumber++;if(this._var.loopNumber>=this._options.loopMaxNumber){clearInterval(this._var.loop);this._var.loop=null;this._var.loopNumber=0;}}
if(detected===true){if(loop===true){this._var.checking=false;}
this._destroyBait();this.emitEvent(true);}else if(this._var.loop===null||loop===false){if(loop===true){this._var.checking=false;}
this._destroyBait();this.emitEvent(false);}};DetectAdBlock.prototype.emitEvent=function(detected){var fns=this._var.event[(detected===true?'detected':'notDetected')];for(var i in fns){if(fns.hasOwnProperty(i)){fns[i]();}}
if(this._options.resetOnEnd===true){this.clearEvent();}
return this;};DetectAdBlock.prototype.clearEvent=function(){this._var.event.detected=[];this._var.event.notDetected=[];};DetectAdBlock.prototype.on=function(detected,fn){this._var.event[(detected===true?'detected':'notDetected')].push(fn);return this;};DetectAdBlock.prototype.onDetected=function(fn){return this.on(true,fn);};DetectAdBlock.prototype.onNotDetected=function(fn){return this.on(false,fn);};window.DetectAdBlock=DetectAdBlock;if(window.detectAdBlock===undefined){window.detectAdBlock=new DetectAdBlock({checkOnLoad:true,resetOnEnd:true});}})(window);nk.lang={close:'close',permission_denied:'Permission Denied',please_login:'Login or register to use this function',login_signup:'Login or Sign Up',dropdown_search:'Search <b>{0}</b>',dropdown_search_in:'Search <b>{0}</b> in {1}'};jQuery.ajaxSetup({beforeSend:function(){$('#ajax_loading').show();},complete:function(){$('#ajax_loading').hide();},success:function(){}});jQuery.timeago.settings.allowFuture=true;jQuery(document).ready(function(){jQuery("span.timeago").timeago();bind_events();});String.prototype.ucfirst=function(){return this.charAt(0).toUpperCase()+this.slice(1);}
String.prototype.format=function(){var args=arguments;return this.replace(/{(\d+)}/g,function(match,number){return typeof args[number]!='undefined'?args[number]:match;});};var logo_animation_timer;var logo_animation_status=false;var search_updating=0;var last_search_value='';var search_drop_count=0;var search_drop_focus=0;var mouse_is_hover_search_drop=0;var search_drop_count_first=0;var header_bottom_opened=0;var home_cycle_working=0;var thread_infobox_timeout=0,thread_infobox_object;function bind_events()
{$('body').on('mouseenter','#logo',function(){logo_animation_timer=setTimeout(function(){logo_animation();logo_animation_status=true;},600);}).on('mouseleave','#logo',function(){clearTimeout(logo_animation_timer);});$('body').on('mouseleave','#logo',function(){setTimeout(function(){if(logo_animation_status==false)return;logo_animation();logo_animation_status=false;},600);});$('body').on('keyup','#top_search',function(){update_top_search(this,0,event);});$('body').on('keydown','#top_search',function(){update_top_search(this,1,event);});$('body').on('focusout','#top_search',function(){top_search_focusout();});$('body').on('mouseenter','#top_search_res_container',function(){mouse_is_hover_search_drop=1;});$('body').on('mouseout','#top_search_res_container',function(){mouse_is_hover_search_drop=0;});$('body').on('click','.top_search_res_bit',function(){search_drop_focus_enter(this);});$('body').on('click','.quoted_extra_clickable',function(){quoted_extra_click(this);});$('body').on('click','#thread_lister_display_opt',function(){$('#threadlister_options').toggle();});$('body').on('click','#threadlister_options_save',function(){threadlister_options_save();});$('body').on('keydown','#threadlister_options',function(e){if(e.keyCode==13){threadlister_options_save();}});$('body').on('click','#thread_lister_infinite',function(){infinite_scroller_enabled=true;threadlister_onscroll();return false;});$('body').on('mouseenter','.post_header_poster',function(){thread_infobox_object=this;thread_infobox_timeout=setTimeout(function(){thread_show_user_infobox();},500);});$('body').on('mouseout','.post_header_poster',function(){clearTimeout(thread_infobox_timeout);if($('.user_infobox:hover').length>0)return;$('.user_infobox').remove();});$('body').on('click','.post_actions_bit_action_reply',function(e){if(!can_perform_user_action_popup(e))e.preventDefault();thread_action_reply(this);});$('body').on('click','.thread_action_reply_preview',function(){thread_action_reply_preview(this);});$('body').on('click','.thread_action_reply_publish',function(){thread_action_reply_publish(this);});$('body').on('click','.thread_action_reply_edit',function(){thread_action_reply_edit(this);});$('body').on('click','.thread_action_reply_close',function(){thread_action_reply_close(this);});$('body').on("click",'.overflow_action',function(){overflow_message_action($(this).attr('action'));});$('body').on('click','.thread_add_reply',function(){thread_action_reply(this);});$('body').on('click','.new_thread_preview',function(){new_thread_preview(this);});$('body').on('click','.new_thread_publish',function(){new_thread_publish(this);});$('body').on('click','.new_thread_edit',function(){new_thread_edit(this);});$('body').on('click','#new_thread_link',function(e){if(!can_perform_user_action_popup(e))e.preventDefault();});$('body').on('click','.home_sidebar_bit',function(){home_sidebar_click(this);});$('body').on('click','.post_actions_bit_action_report',function(e){});$('body').on('click','.post_actions_bit_action_raw',function(e){if(!can_perform_user_action_popup(e))e.preventDefault();});}
var home_sidebar_click_timeout;function home_sidebar_click(e)
{clearTimeout(home_sidebar_click_timeout);if($(e).hasClass('home_sidebar_bit_active'))
{$(e).removeClass('home_sidebar_bit_active');}
else
{$(e).addClass('home_sidebar_bit_active');}
home_sidebar_click_timeout=setTimeout(function(){home_sidebar_click_update();},500);}
function home_sidebar_click_update()
{var res=Array();$("#home_lister").html('<div style="font-size:20px;font-family: sans-serif;padding: 15px 10px;">Loading...</div>');$(".home_sidebar_bit_active").each(function(i){res.push($(this).attr('cid'));});$.get("https://narkive.com/?home_categories="+res.join(','),function(data){$("#home_lister").html(data);jQuery("span.timeago").timeago();});}
function logo_animation_bit(what)
{if(what=='ml')
var opposite='ng'
else
var opposite='ml';$('#logo_desc_'+what).animate({'top':'10px','opacity':0},'normal',function(){$('#logo_desc_'+what).css('display','none').css('top','0');});$('#logo_desc_'+opposite).css('opacity','0').css('display','block').css('top','-10px');$('#logo_desc_'+opposite).animate({'top':'0px','opacity':1},'normal');}
function logo_animation()
{if($('#logo_desc_ml').css('display')=='none')
logo_animation_bit('ng');else
logo_animation_bit('ml');}
function search_drop_focus_select(value)
{search_drop_focus=value;var i=0;for(i=1;i<=search_drop_count;i++)
{if(i==search_drop_focus)
{$('#top_search_res_bit'+i).css('background-color','#ECFCFE');}
else
{$('#top_search_res_bit'+i).css('background-color','white');}}}
function search_drop_focus_enter(e)
{if(search_drop_focus==0||$('#top_search_res_bit'+search_drop_focus).attr('action')=='search')
{location.href='https://narkive.com/search?q='+$('#top_search').val();}
else if($('#top_search_res_bit'+search_drop_focus).attr('action')=='search_newsgroup')
{var domain=document.domain;domain=domain.split('.narkive.com');location.href='https://narkive.com/search?q='+$('#top_search').val()+" group:"+domain[0];}
else
{location.href=$('#top_search_res_bit'+search_drop_focus).attr('href');}}
function get_text_width(text)
{if($('#get_text_width').length==0)
{$('body').append('<span style="display: none" id="get_text_width">'+text+'</span>');}
else
{$('#get_text_width').html(text);}
return $('#get_text_width').width();}
function top_search_focusout()
{setTimeout(function(){if(mouse_is_hover_search_drop==0)
{$('#top_search_res_container').css('display','none');$('#top_search').css('width','');}},50);}
function update_top_search(e,swich,event)
{var keynum=0;if(window.event){keynum=event.keyCode;}
else if(event.which){keynum=event.which;}
if(swich==1&&(keynum==38||keynum==40||keynum==13))
{if(keynum==40){if(search_drop_focus<search_drop_count)
{if($('#top_search_res_bit'+search_drop_focus).length!=0)
{$('#top_search_res_bit'+search_drop_focus).css('background-color','');}
search_drop_focus+=1;$('#top_search_res_bit'+search_drop_focus).css('background-color','#ECFCFE');}}
if(keynum==38){if(search_drop_focus>0)
{if($('#top_search_res_bit'+search_drop_focus).length!=0)
{$('#top_search_res_bit'+search_drop_focus).css('background-color','');}
search_drop_focus-=1;$('#top_search_res_bit'+search_drop_focus).css('background-color','#ECFCFE');}}
if(keynum==13){search_drop_focus_enter(e);}}
else if(e.value!=''&&(last_search_value!=e.value||$('#top_search_res_container').css('display')=='none'))
{search_drop_count=0;last_search_value=e.value;$('#top_search_res_container').css('display','block');var append='<div id="top_search_res">';search_drop_count+=1;append+='<div id="top_search_res_bit'+search_drop_count+'" class="top_search_res_bit" action="search" res_id="'+search_drop_count+'">';append+=nk.lang.dropdown_search.format(e.value);append+='</div>';var domain=document.domain;domain=domain.split('.narkive.com');if(domain[0]!='narkive.com')
{search_drop_count+=1;append+='<div id="top_search_res_bit'+search_drop_count+'" class="top_search_res_bit" action="search_newsgroup" res_id="'+search_drop_count+'">';append+=nk.lang.dropdown_search_in.format(e.value,domain[0])
append+='</div>';}
append+='<div id="top_search_res_bit_request_result"></div>';$('#top_search_res_container').html(append);search_drop_count_first=search_drop_count;if(!search_updating||1==1)
{search_updating=1;$.getJSON("https://"+document.domain+"/ajax/searchcat?limit=5&query="+encodeURIComponent(e.value),function(data){var append='';search_drop_count=search_drop_count_first;jQuery.each(data,function(key,bit)
{var offset=get_text_width('<span class="top_search_res_bit" style="font-family: Arial; font-size: 13px;">&#8594; '+bit.html+'</span>');if($('#top_search').width()<offset)
{$('#top_search').css('width',offset);$('#top_search_res').css('width',offset+8);}
search_drop_count+=1;append+='<div class="top_search_res_bit" id="top_search_res_bit'+search_drop_count+'" res_id="'+search_drop_count+'" href="'+bit.url+'">&#8594; '+bit.html+'</div>';});$('#top_search_res_bit_request_result').html(append);search_updating=0;$(".top_search_res_bit").hover(function(){search_drop_focus_select($(this).attr('res_id'));});search_drop_focus=0;$('.top_search_res_bit').click(function(){search_drop_focus_enter(this);});});}
$(".top_search_res_bit").hover(function(){search_drop_focus_select($(this).attr('res_id'));});$('.top_search_res_bit').click(function(){search_drop_focus_enter(this);});search_drop_focus=0;if(domain[0]!='narkive.com')
{var offset_a=get_text_width('<span class="top_search_res_bit" style="font-family: Arial; font-size: 13px;">'+'Search for groups named <b>'+e.value+'</b>'+'</span>');var offset_b=get_text_width('<span class="top_search_res_bit" style="font-family: Arial; font-size: 13px;">'+'Search <b>'+e.value+'</b> in '+domain[0]+'</span>');if(offset_b>offset_a)
{offset=offset_b;}
else
{offset=offset_a;}}
else
{var offset=get_text_width('<span class="top_search_res_bit" style="font-family: Arial; font-size: 13px;">'+'Search for groups named <b>'+e.value+'</b>'+'</span>');}
if(offset>222)
{$('#top_search').css('width',offset);$('#top_search_res').css('width',offset+32);}
else
{$('#top_search').css('width',222);$('#top_search_res').css('width',222+32);}
if(search_drop_focus>search_drop_count)
{search_drop_focus=search_drop_count;}}
else if(e.value.length==0)
{$('#top_search_res_container').css('display','none');$('#top_search').css('width','');}}
function threadlister_options_save()
{$('#threadlister_options').css('display','none');$('#thread_lister_infinite').css('display','none');$(".thread_lister_bit").remove();$(".threadlister_slidedown").remove();$('#thread_lister_infinite').before('<div id="thread_lister_filler">Saving Display Options...</div>');$.ajax({url:'//'+document.domain+'/ajax/setthreadlistercookie?count='+$('#threadlister_options_count').val()+'&value='+$('#threadlister_options_value').val(),cache:false}).done(function(){$('#thread_lister_filler').html('Options Saved, Reloading...');$.get('//'+document.domain+'/?ajax').done(function(html){$('#thread_lister_infinite').before(html);$('#thread_lister_infinite').css('display','block');$('#thread_lister_filler').remove();infinite_scroller_enabled=false;jQuery("span.timeago").timeago();}).fail(function(){$('#thread_lister_filler').html('Couldn\'t Reload, Retrying Manually...');document.location.reload(true);});}).fail(function(){$('#thread_lister').html('<div id="thread_lister_filler">Couldn\'t Save Options, Please Retry</div>');$('#threadlister_options').css('display','block');});}
function is_element_in_viewport(el)
{if(typeof jQuery==="function"&&el instanceof jQuery)
{el=el[0];}
var rect=el.getBoundingClientRect();return(rect.top>=0&&rect.left>=0&&rect.bottom<=(window.innerHeight||document.documentElement.clientHeight)&&rect.right<=(window.innerWidth||document.documentElement.clientWidth));}
var threadlister_is_loading=false,infinite_scroller_enabled=false;function threadlister_onscroll()
{if(is_element_in_viewport($('#thread_lister_infinite'))&&!threadlister_is_loading&&infinite_scroller_enabled)
{$('#thread_lister_infinite').html('Loading More...<img src="https://narkive.com/threadlister_loader.gif" style="margin-left: 24px;">');threadlister_is_loading=true;$.get('//'+document.domain+'/?ajax&offset='+$(".thread_lister_bit").length).done(function(html){thread_lister_bit_lenght=$(".thread_lister_bit").length;html='<div class="threadlister_slidedown" id="slidedown_'+thread_lister_bit_lenght+'">threads starting from #'+$(".thread_lister_bit").length+'</div>'+html;$('#thread_lister_infinite').before(html);jQuery("span.timeago").timeago();$('#thread_lister_infinite').html('Click to Load More...');location.hash='#slidedown_'+thread_lister_bit_lenght;setTimeout(function(){threadlister_is_loading=false;},50);}).fail(function(){$('#thread_lister_infinite').html('Failed in loading more');document.location.reload(true);});}}
function thread_show_user_infobox()
{$.get('//'+document.domain+'/user/'+$(thread_infobox_object).attr('hash')+':infobox').done(function(html){$('.user_infobox').remove();$(thread_infobox_object).append('<div class="user_infobox">'+html+'</div>');});}
function thread_action_reply(e){if(!can_perform_user_action_popup())
{return false;}
var post_id=$(e).parents('.post').attr('id');if(typeof post_id==='undefined')
post_id=1;else
post_id=post_id.replace('post','');$.get("https://"+document.domain+"/ajax/quotepost?hash="+nk.conf.thread_hash+"&post="+post_id,function(data){$('.action_reply_container').remove();var html='<div class="action_reply_container standard_input"><textarea>'+data+'</textarea><div class="action_reply_buttons"><div class="action_reply_buttons_bit thread_action_reply_close" style="float: left;">Close</div><div class="action_reply_buttons_bit thread_action_reply_publish">Publish</div><div class="action_reply_buttons_bit thread_action_reply_preview">Preview</div><div class="action_reply_buttons_bit thread_action_reply_edit" style="display: none;">Edit</div></div></div>'
$('#post'+post_id).append(html);var old_val=$('.action_reply_container textarea').val();$('.action_reply_container textarea').focus().val('').val(old_val+"\n");$('.action_reply_container textarea').autosize();$('#thread_container .post_header, #thread_container .post_body, #sidebar_container, #header, #thread_lister_ctrl, #footer').css('opacity',0.3);$(window).scrollTop($('.action_reply_container textarea').offset().top-(0.4*($(window).height()-$('.action_reply_container textarea').height())/ 2));});}
function thread_action_reply_preview(e){$.post("https://"+document.domain+"/ajax/previewpost",{hash:nk.conf.thread_hash,post:$('.action_reply_container textarea').val()},function(data){$('.action_reply_container textarea').hide();$('.action_reply_container').prepend(data);jQuery("span.timeago").timeago();init_quoted_extra();$('.thread_action_reply_preview').hide();$('.thread_action_reply_edit').show();});}
function thread_action_reply_publish(e){$('.action_reply_buttons_bit').css('opacity',0.4);$('.action_reply_buttons_bit').css('cursor','default');$(".action_reply_buttons").click(function(){return false;});$.post("https://"+document.domain+"/ajax/reply",{hash:nk.conf.thread_hash,post:$('.action_reply_container textarea').val(),reply_to:$(e).parents('.post').attr('id').replace('post',''),csrf:nk.conf.csrf},function(data){eval(data);$('.action_reply_buttons_bit').css('opacity',1);$('.action_reply_buttons_bit').css('cursor','pointer');$(".action_reply_buttons").unbind('click');});}
function thread_action_reply_edit(e){$('.thread_action_reply_preview').show();$('.thread_action_reply_edit').hide();$('.action_reply_container .post').remove();$('.action_reply_container textarea').show();}
function thread_action_reply_close(e){$('.action_reply_container').remove();$('#thread_container .post_header, #thread_container .post_body, #sidebar_container, #header, #thread_lister_ctrl, #footer').css('opacity',1);}
function overflow_message(header,content,actions,width)
{if(typeof width==='undefined')
width=400;$('#overflow_message').css('display','table');$('#overflow').css('display','block');if($(window).width()>=770)
{$('#overflow_message').css('width',width+'px');$('#overflow_message').css('left','calc(50% - '+(width/2)+'px)');}
$('#overflow_message_header').html(header);$('#overflow_message_content').html(content);var r='';for(key in actions)
{if(typeof actions[key].align==='undefined')
actions[key].align='right';r+='<div class="overflow_action" style="float: '+actions[key].align+';" action="'+actions[key].action+'">'+actions[key].text+'</div>'}
$('#overflow_message_actions').html(r);}
function overflow_message_action(action)
{if(action=='close')
{$('#overflow_message').css('display','none');$('#overflow').css('display','none');}
if(action=='send_to_login')
{location.href='https://narkive.com/user/login';}
if(action=='send_to_edit_username')
{window.open('https://narkive.com/user/profile_edit','_blank');}
if(action=='post_privacy_warning_ignore'||action=='post_privacy_warning_save')
{overflow_message_action('close');$('.action_reply_buttons_bit').css('opacity',0.4);$('.action_reply_buttons_bit').css('cursor','default');$(".action_reply_buttons").click(function(){return false;});$.post("https://"+document.domain+"/ajax/reply?privacy="+action.replace('post_privacy_warning_',''),{hash:nk.conf.thread_hash,post:$('.action_reply_container textarea').val(),reply_to:$('.action_reply_container ').parents('.post').attr('id').replace('post',''),csrf:nk.conf.csrf},function(data){eval(data);$('.action_reply_buttons_bit').css('opacity',1);$('.action_reply_buttons_bit').css('cursor','pointer');$(".action_reply_buttons").unbind('click');});''}
if(action=='thread_privacy_warning_ignore'||action=='thread_privacy_warning_save')
{overflow_message_action('close');$('.new_thread_buttons_bit').css('opacity',0.4);$('.new_thread_buttons_bit').css('cursor','default');$(".new_thread_buttons").click(function(){return false;});$.post("https://"+document.domain+"/add?ajax&privacy="+action.replace('thread_privacy_warning_',''),{post:$('.new_thread textarea').val(),title:$('input[name=\'title\']').val(),csrf:nk.conf.csrf},function(data){eval(data);$('.new_thread_buttons_bit').css('opacity',1);$('.new_thread_buttons_bit').css('cursor','pointer');$(".new_thread_buttons").unbind('click');});}
if(action=='admin_eval_a')
{var_admin_eval_a();}}
function can_perform_user_action()
{return nk.conf.logged_in;}
function can_perform_user_action_popup()
{if(!can_perform_user_action())
{overflow_message(nk.lang.permission_denied,nk.lang.please_login,{1:{'action':'close','text':nk.lang.close.ucfirst()},2:{'action':'send_to_login','text':nk.lang.login_signup}});ga('send','event','user','please_login',{'nonInteraction':1});return false;}
else
{return true;}}