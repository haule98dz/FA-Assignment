var abs_offs = 0;
var result = '';
var offs = 0;
var real_offs = '0x0000';

function ok() {
    var reg;
    var fullReg;
    var stringOffs = $('#offs').val()
    var temp = parseInt(stringOffs,16)
    offs = temp - abs_offs
    abs_offs = temp
    reg = $('#reg').val()
    fullReg = $('#full').val()
    result += (`    uint${offs*8}_t ${reg}    /* ${fullReg} (${offs} bytes at offset ${real_offs})*/\n`);
    $('#result').val(result)
    real_offs = stringOffs;
}

function undo() {
    result = result.substring(0, 1 + result.lastIndexOf('\n', result.length - 4))
    $('#result').val(result)
    abs_offs -= offs;
}



function toint(s) {
    return parseInt(s, 16);
}