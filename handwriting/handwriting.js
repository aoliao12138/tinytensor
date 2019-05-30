/**
 * Created by perry on 16/1/15.
 */
var myArray = new Array()
var myIndex = 0
var canvasWidth = Math.min(280, $(window).width() - 20);
var canvasHeight = canvasWidth;

var isMouseDown = false;
var lastLoc = {x: 0, y: 0};
var lastTimeStamp = 0;
var lastLineWidth = -1;
var strokeColor = "black";
var canvas = document.getElementById("canvas");
var context = canvas.getContext("2d");

canvas.width = canvasWidth;
canvas.height = canvasHeight;

$("#controller").css("width", canvasWidth + "px");
drawGrid();


$("#clear_btn").click(
    function (e) {
        context.clearRect(0, 0, canvasWidth, canvasHeight);
        drawGrid();
        downloadTextFile();
        myArray = [];
    }
);

$(".color_btn").click(function (e) {
    $(".color_btn").removeClass("color_btn_selected");
    $(this).addClass("color_btn_selected");
    strokeColor = $(this).css("background-color");
});

//document.onmousedown = function (e) {
//    alert(e.clientX + "," + e.clientY);
//};
/*开始时*/
function beginStroke(point) {
    isMouseDown = true;
    var loc = windowToCanvas(point.x, point.y);
    lastLoc = loc;
    lastTimeStamp = new Date().getTime();
}
/*结束后*/
function endStroke() {
    isMouseDown = false;
}
/*绘制过程中的动作*/
function moveStroke(point) {
    var curLoc = windowToCanvas(point.x, point.y);

    myArray[myIndex ++] = parseInt(curLoc.x / 10, 10)
    myArray[myIndex ++] = ' '
    myArray[myIndex ++] = parseInt(curLoc.y / 10, 10)
    myArray[myIndex ++] = '\n'

    console.log(parseInt(curLoc.x / 10, 10))
    console.log(parseInt(curLoc.y / 10, 10))



    var curTimeStamp = new Date().getTime();
    var s = calcDistance(curLoc, lastLoc);
    var t = curTimeStamp - lastTimeStamp;

    var lineWidth = calcLineWidth(t, s);
    //draw

    context.beginPath();
    context.moveTo(lastLoc.x, lastLoc.y);
    context.lineTo(curLoc.x, curLoc.y);

    context.strokeStyle = strokeColor;
    context.lineWidth = lineWidth;
    context.lineCap = "round";
    context.linejoin = "round";
    context.stroke();

    lastLoc = curLoc;
    lastTimeStamp = curTimeStamp;
    lastLineWidth = lineWidth;
}

canvas.onmousedown = function (e) {
    e.preventDefault();
    beginStroke({x: e.clientX, y: e.clientY});
};
canvas.onmouseup = function (e) {
    e.preventDefault();
    endStroke();
};
canvas.onmouseout = function (e) {
    e.preventDefault();
    endStroke();
};
canvas.onmousemove = function (e) {
    e.preventDefault();
    if (isMouseDown) {
        moveStroke({x: e.clientX, y: e.clientY});
    }
};
var touch;
/*触控事件*/
canvas.addEventListener("touchstart", function (e) {
    e.preventDefault();
    touch = e.touches[0];
    beginStroke({x: touch.pageX, y: touch.pageY});
});
canvas.addEventListener("touchmove", function (e) {
    e.preventDefault();
    if (isMouseDown) {
        touch = e.touches[0];
        moveStroke({x: touch.pageX, y: touch.pageY});
    }
});
canvas.addEventListener("touchend", function (e) {
    e.preventDefault();
    endStroke();
});
/*计算要绘制线条的宽*/
function calcLineWidth(t, s) {
    var v = s / t;

    var resultLineWidth;
    if (v <= 0.1) {
        resultLineWidth = 30;
    } else if (v >= 10) {
        resultLineWidth = 1;
    } else {
        resultLineWidth = 30 - (v - 0.1) / (10 - 0.1) * (30 - 1);
    }
    if (lastLineWidth = -1) {
        return resultLineWidth;
    }
    return lastLineWidth * 2 / 3 + resultLineWidth * 1 / 3;
}

/*求两坐标间的距离*/
function calcDistance(loc1, loc2) {
    return Math.sqrt((loc1.x - loc2.x) * (loc1.x - loc2.x) + (loc1.y - loc2.y) * (loc1.y - loc2.y));//x轴距离的平方与上y轴距离的平方的和再开根号;
}

/*获取canvas上的坐标点*/
function windowToCanvas(x, y) {
    var bbox = canvas.getBoundingClientRect();
    return {x: Math.round(x - bbox.left), y: Math.round(y - bbox.top)};
}

/*绘米字格*/
function drawGrid() {
    context.save();

    context.strokeStyle = "rgb(230,11,9)";

    context.beginPath();
    context.moveTo(3, 3);
    context.lineTo(canvasWidth - 3, 3);
    context.lineTo(canvasHeight - 3, canvasHeight - 3);
    context.lineTo(3, canvasHeight - 3);
    context.closePath();

    context.lineWidth = 6;
    context.stroke();

    context.beginPath();
    context.moveTo(0, 0);
    context.lineWidth = 1;
    context.stroke();

    context.restore();
}


/* FileSaver.js
 * A saveAs() FileSaver implementation.
 * 1.3.2
 * 2016-06-16 18:25:19
 *
 * By Eli Grey, http://eligrey.com
 * License: MIT
 *   See https://github.com/eligrey/FileSaver.js/blob/master/LICENSE.md
 */
 
/*global self */
/*jslint bitwise: true, indent: 4, laxbreak: true, laxcomma: true, smarttabs: true, plusplus: true */
 
/*! @source http://purl.eligrey.com/github/FileSaver.js/blob/master/FileSaver.js */
 
var saveAs = saveAs || (function(view) {
    "use strict";
    // IE <10 is explicitly unsupported
    if (typeof view === "undefined" || typeof navigator !== "undefined" && /MSIE [1-9]\./.test(navigator.userAgent)) {
        return;
    }
    var
          doc = view.document
          // only get URL when necessary in case Blob.js hasn't overridden it yet
        , get_URL = function() {
            return view.URL || view.webkitURL || view;
        }
        , save_link = doc.createElementNS("http://www.w3.org/1999/xhtml", "a")
        , can_use_save_link = "download" in save_link
        , click = function(node) {
            var event = new MouseEvent("click");
            node.dispatchEvent(event);
        }
        , is_safari = /constructor/i.test(view.HTMLElement) || view.safari
        , is_chrome_ios =/CriOS\/[\d]+/.test(navigator.userAgent)
        , throw_outside = function(ex) {
            (view.setImmediate || view.setTimeout)(function() {
                throw ex;
            }, 0);
        }
        , force_saveable_type = "application/octet-stream"
        // the Blob API is fundamentally broken as there is no "downloadfinished" event to subscribe to
        , arbitrary_revoke_timeout = 1000 * 40 // in ms
        , revoke = function(file) {
            var revoker = function() {
                if (typeof file === "string") { // file is an object URL
                    get_URL().revokeObjectURL(file);
                } else { // file is a File
                    file.remove();
                }
            };
            setTimeout(revoker, arbitrary_revoke_timeout);
        }
        , dispatch = function(filesaver, event_types, event) {
            event_types = [].concat(event_types);
            var i = event_types.length;
            while (i--) {
                var listener = filesaver["on" + event_types[i]];
                if (typeof listener === "function") {
                    try {
                        listener.call(filesaver, event || filesaver);
                    } catch (ex) {
                        throw_outside(ex);
                    }
                }
            }
        }
        , auto_bom = function(blob) {
            // prepend BOM for UTF-8 XML and text/* types (including HTML)
            // note: your browser will automatically convert UTF-16 U+FEFF to EF BB BF
            if (/^\s*(?:text\/\S*|application\/xml|\S*\/\S*\+xml)\s*;.*charset\s*=\s*utf-8/i.test(blob.type)) {
                return new Blob([String.fromCharCode(0xFEFF), blob], {type: blob.type});
            }
            return blob;
        }
        , FileSaver = function(blob, name, no_auto_bom) {
            if (!no_auto_bom) {
                blob = auto_bom(blob);
            }
            // First try a.download, then web filesystem, then object URLs
            var
                  filesaver = this
                , type = blob.type
                , force = type === force_saveable_type
                , object_url
                , dispatch_all = function() {
                    dispatch(filesaver, "writestart progress write writeend".split(" "));
                }
                // on any filesys errors revert to saving with object URLs
                , fs_error = function() {
                    if ((is_chrome_ios || (force && is_safari)) && view.FileReader) {
                        // Safari doesn't allow downloading of blob urls
                        var reader = new FileReader();
                        reader.onloadend = function() {
                            var url = is_chrome_ios ? reader.result : reader.result.replace(/^data:[^;]*;/, 'data:attachment/file;');
                            var popup = view.open(url, '_blank');
                            if(!popup) view.location.href = url;
                            url=undefined; // release reference before dispatching
                            filesaver.readyState = filesaver.DONE;
                            dispatch_all();
                        };
                        reader.readAsDataURL(blob);
                        filesaver.readyState = filesaver.INIT;
                        return;
                    }
                    // don't create more object URLs than needed
                    if (!object_url) {
                        object_url = get_URL().createObjectURL(blob);
                    }
                    if (force) {
                        view.location.href = object_url;
                    } else {
                        var opened = view.open(object_url, "_blank");
                        if (!opened) {
                            // Apple does not allow window.open, see https://developer.apple.com/library/safari/documentation/Tools/Conceptual/SafariExtensionGuide/WorkingwithWindowsandTabs/WorkingwithWindowsandTabs.html
                            view.location.href = object_url;
                        }
                    }
                    filesaver.readyState = filesaver.DONE;
                    dispatch_all();
                    revoke(object_url);
                }
            ;
            filesaver.readyState = filesaver.INIT;
 
            if (can_use_save_link) {
                object_url = get_URL().createObjectURL(blob);
                setTimeout(function() {
                    save_link.href = object_url;
                    save_link.download = name;
                    click(save_link);
                    dispatch_all();
                    revoke(object_url);
                    filesaver.readyState = filesaver.DONE;
                });
                return;
            }
 
            fs_error();
        }
        , FS_proto = FileSaver.prototype
        , saveAs = function(blob, name, no_auto_bom) {
            return new FileSaver(blob, name || blob.name || "download", no_auto_bom);
        }
    ;
    // IE 10+ (native saveAs)
    if (typeof navigator !== "undefined" && navigator.msSaveOrOpenBlob) {
        return function(blob, name, no_auto_bom) {
            name = name || blob.name || "download";
 
            if (!no_auto_bom) {
                blob = auto_bom(blob);
            }
            return navigator.msSaveOrOpenBlob(blob, name);
        };
    }
 
    FS_proto.abort = function(){};
    FS_proto.readyState = FS_proto.INIT = 0;
    FS_proto.WRITING = 1;
    FS_proto.DONE = 2;
 
    FS_proto.error =
    FS_proto.onwritestart =
    FS_proto.onprogress =
    FS_proto.onwrite =
    FS_proto.onabort =
    FS_proto.onerror =
    FS_proto.onwriteend =
        null;
 
    return saveAs;
}(
       typeof self !== "undefined" && self
    || typeof window !== "undefined" && window
    || this.content
));
// `self` is undefined in Firefox for Android content script context
// while `this` is nsIContentFrameMessageManager
// with an attribute `content` that corresponds to the window
 
if (typeof module !== "undefined" && module.exports) {
  module.exports.saveAs = saveAs;
} else if ((typeof define !== "undefined" && define !== null) && (define.amd !== null)) {
  define("FileSaver.js", function() {
    return saveAs;
  });
}


var downloadTextFile = function(mobileCode) {
    // console.log(mobileCode.x, mobileCode.y)
    
    for (i = 0; i < myArray.length; i++) { 
        console.log(myArray[i].x, myArray[i].y)
    }
    var file = new File(myArray, "data.txt", { type: "text/plain;charset=utf-8" });
    saveAs(file);
}