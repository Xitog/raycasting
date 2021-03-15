// -----------------------------------------------------------
// Common Canvas Library for JavaScript (April-June 2020)
// -----------------------------------------------------------
// MIT Licence (Expat License Wording)
// -----------------------------------------------------------
// Copyright © 2020, Damien Gouteux
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
// For more information visit:
// https://xitog.github.io/dgx/

var has_translated = [];

//-----------------------------------------------------------------------------
// Getters and setters
//-----------------------------------------------------------------------------

function get(id) {
    return document.getElementById(id);
}

function getBool(id) {
    return document.getElementById(id).checked;
}

function setBool(id, val) {
    document.getElementById(id).checked = val;
}

function getFloat(id) {
    return parseFloat(document.getElementById(id).value);
}

function setFloat(id, val) {
    document.getElementById(id).value = val;
}

//-----------------------------------------------------------------------------
// Drawing functions
//-----------------------------------------------------------------------------

function circle(ctx, color, x, y, r) {
    ctx.strokeStyle = color;
    ctx.beginPath();
    ctx.arc(x, y, r, 0, 2 * Math.PI);
    ctx.stroke();
}

function line(ctx, color, x1, y1, x2, y2) {
    ctx.strokeStyle = color;
    ctx.beginPath();
    ctx.moveTo(x1, y1);
    ctx.lineTo(x2, y2);
    ctx.stroke();
}

function rect(ctx, color, x, y, w, h, fill) {
    if (fill) {
        ctx.fillStyle = color;
        ctx.fillRect(x, y, w, h);
    } else {
        ctx.strokeStyle = color;
        ctx.strokeRect(x, y, w, h);
    }
}

function text(ctx, txt, font, color, x, y, fill) {
    ctx.font = font;
    if (fill) {
        ctx.fillStyle = color;
        ctx.fillText(txt, x, y);
    } else {
        ctx.strokeStyle = color;
        ctx.strokeText(txt, x, y);
    }
}

//-----------------------------------------------------------------------------
// Set and get the screen
//-----------------------------------------------------------------------------

function init(id='screen') {
    let screen = document.getElementById(id);
    let context = screen.getContext('2d');
    if (!has_translated.includes(id)) {
        context.translate(0.5, 0.5);
        context.globalCompositeOperation = 'normal'; // source-over by default
        has_translated.push(id);
    }
    return { screen, context }
}
