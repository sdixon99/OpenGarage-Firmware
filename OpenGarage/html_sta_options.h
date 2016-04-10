const char html_sta_options[] PROGMEM = R"(<body>
<div data-role='page' id='page_opts'>
<div data-role='header'><h3>Edit Options</h3></div>    
<div data-role='content'>   
<table cellpadding=2>
<tr><td><b>Accessibility:</b></td><td>
<select name='acc' id='acc' data-mini='true'>
<option value=0>Direct IP Only</option>
<option value=1>Direct IP + Cloud</option>                  
<option value=2>Cloud Only</option>
</select></td></tr>      
<tr><td><b>Cloud Token:</b></td><td><input type='text' size=24 maxlength=32 id='auth' data-mini='true' value='-'></td></tr>
<tr><td><b>Mount Type:</b></td><td>
<select name='mnt' id='mnt' data-mini='true'>
<option value=0>Ceiling Mount</option>
<option value=1>Side Mount</option>
</select></td></tr> 
<tr><td><b>Threshold (cm): </b></td><td><input type='text' size=4 maxlength=4 id='dth' data-mini='true' value=1></td></tr>
<tr><td><b>Read Interval (s):</b></td><td><input type='text' size=3 maxlength=3 id='riv' data-mini='true' value=1></td></tr>
<tr><td><b>Device Name:</b></td><td><input type='text' size=20 maxlength=32 id='name' data-mini='true' value='-'></td></tr>
<tr><td><b>HTTP Port:</b></td><td><input type='text' size=5 maxlength=5 id='htp' value=1 data-mini='true'></td></tr>
<tr><td><b>Device Key:</b></td><td><input type='password' size=24 maxlength=32 id='dkey' data-mini='true'></td></tr>
<tr><td colspan=2><p id='msg'></p></td></tr>
</table>
<div data-role='controlgroup' data-type='horizontal'>
<a href='#' data-role='button' data-inline='true' data-theme='a' id='btn_cancel'>Cancel</a>
<a href='#' data-role='button' data-inline='true' data-theme='b' id='btn_submit'>Submit</a>      
</div>
<table>
<tr><td colspan=2><input type='checkbox' data-mini='true' id='cb_key'><label for='cb_key'>Change Device Key</label></td></tr>
<tr><td><b>New Key:</b></td><td><input type='password' size=24 maxlength=32 id='nkey' data-mini='true' disabled></td></tr>
<tr><td><b>Confirm:</b></td><td><input type='password' size=24 maxlength=32 id='ckey' data-mini='true' disabled></td></tr>      
</table>
</div>
<div data-role='footer' data-theme='c'>
<p>&nbsp; OpenGarage Firmware <label id='fwv'>-</label>&nbsp;<a href="update" target='_blank' data-role='button' data-inline=true data-mini=true>Update</a></p>
</div> 
</div>
<script>
function clear_msg() {$('#msg').text('');}  
function show_msg(s) {$('#msg').text(s).css('color','red'); setTimeout(clear_msg, 2000);}
$('#cb_key').click(function(e){
$('#nkey').textinput($(this).is(':checked')?'enable':'disable');
$('#ckey').textinput($(this).is(':checked')?'enable':'disable');
});
$('#btn_cancel').click(function(e){
e.preventDefault(); close();
});
$('#btn_submit').click(function(e){
e.preventDefault();
if(confirm('Submit changes?')) {
var comm='co?dkey='+encodeURIComponent($('#dkey').val());
comm+='&acc='+$('#acc').val();
comm+='&mnt='+$('#mnt').val();
comm+='&dth='+$('#dth').val();
comm+='&riv='+$('#riv').val();
comm+='&htp='+$('#htp').val();
comm+='&name='+encodeURIComponent($('#name').val());
comm+='&auth='+encodeURIComponent($('#auth').val());
if($('#cb_key').is(':checked')) {
if(!$('#nkey').val()) {
if(!confirm('New device key is empty. Are you sure?')) return;
}
comm+='&nkey='+encodeURIComponent($('#nkey').val());
comm+='&ckey='+encodeURIComponent($('#ckey').val());
}
$.getJSON(comm, function(jd) {
if(jd.result!=1) {
if(jd.result==2) show_msg('Check device key and try again.');
else show_msg('Error code: '+jd.result+', item: '+jd.item);
} else {
$('#msg').html('<font color=green>Options are successfully saved. Note that<br>changes to some options may require a reboot.</font>');
$('#btn_submit').
setTimeout(close, 4000);
}
});
}
});
$(document).ready(function() {
$.getJSON('jo', function(jd) {
$('#fwv').text('v'+(jd.fwv/100>>0)+'.'+(jd.fwv/10%10>>0)+'.'+(jd.fwv%10>>0));
$('#acc').val(jd.acc).selectmenu('refresh');
$('#mnt').val(jd.mnt).selectmenu('refresh');
$('#dth').val(jd.dth);
$('#riv').val(jd.riv);
$('#htp').val(jd.htp);
$('#name').val(jd.name);
$('#auth').val(jd.auth);
});
});
</script>
</body>)";
