(function() {
    /*

        Copyright The Closure Library Authors.
        SPDX-License-Identifier: Apache-2.0
       */
    'use strict';
    var l;

    function aa(a) { var b = 0; return function() { return b < a.length ? { done: !1, value: a[b++] } : { done: !0 } } }

    function ba(a) { var b = "undefined" != typeof Symbol && Symbol.iterator && a[Symbol.iterator]; return b ? b.call(a) : { next: aa(a) } }

    function n(a) {
        if (!(a instanceof Array)) {
            a = ba(a);
            for (var b, c = []; !(b = a.next()).done;) c.push(b.value);
            a = c
        }
        return a
    }
    var ca = "function" == typeof Object.defineProperties ? Object.defineProperty : function(a, b, c) {
        if (a == Array.prototype || a == Object.prototype) return a;
        a[b] = c.value;
        return a
    };

    function da(a) { a = ["object" == typeof globalThis && globalThis, a, "object" == typeof window && window, "object" == typeof self && self, "object" == typeof global && global]; for (var b = 0; b < a.length; ++b) { var c = a[b]; if (c && c.Math == Math) return c } throw Error("Cannot find global object"); }
    var ea = da(this);

    function p(a, b) {
        if (b) {
            var c = ea;
            a = a.split(".");
            for (var d = 0; d < a.length - 1; d++) {
                var e = a[d];
                e in c || (c[e] = {});
                c = c[e]
            }
            a = a[a.length - 1];
            d = c[a];
            b = b(d);
            b != d && null != b && ca(c, a, { configurable: !0, writable: !0, value: b })
        }
    }
    p("Promise", function(a) {
        function b(f) {
            this.b = 0;
            this.c = void 0;
            this.a = [];
            var h = this.f();
            try { f(h.resolve, h.reject) } catch (k) { h.reject(k) }
        }

        function c() { this.a = null }

        function d(f) { return f instanceof b ? f : new b(function(h) { h(f) }) }
        if (a) return a;
        c.prototype.b = function(f) {
            if (null == this.a) {
                this.a = [];
                var h = this;
                this.c(function() { h.h() })
            }
            this.a.push(f)
        };
        var e = ea.setTimeout;
        c.prototype.c = function(f) { e(f, 0) };
        c.prototype.h = function() {
            for (; this.a && this.a.length;) {
                var f = this.a;
                this.a = [];
                for (var h = 0; h < f.length; ++h) {
                    var k =
                        f[h];
                    f[h] = null;
                    try { k() } catch (m) { this.f(m) }
                }
            }
            this.a = null
        };
        c.prototype.f = function(f) { this.c(function() { throw f; }) };
        b.prototype.f = function() {
            function f(m) { return function(r) { k || (k = !0, m.call(h, r)) } }
            var h = this,
                k = !1;
            return { resolve: f(this.u), reject: f(this.h) }
        };
        b.prototype.u = function(f) {
            if (f === this) this.h(new TypeError("A Promise cannot resolve to itself"));
            else if (f instanceof b) this.D(f);
            else {
                a: switch (typeof f) {
                    case "object":
                        var h = null != f;
                        break a;
                    case "function":
                        h = !0;
                        break a;
                    default:
                        h = !1
                }
                h ? this.s(f) : this.i(f)
            }
        };
        b.prototype.s = function(f) { var h = void 0; try { h = f.then } catch (k) { this.h(k); return } "function" == typeof h ? this.F(h, f) : this.i(f) };
        b.prototype.h = function(f) { this.j(2, f) };
        b.prototype.i = function(f) { this.j(1, f) };
        b.prototype.j = function(f, h) {
            if (0 != this.b) throw Error("Cannot settle(" + f + ", " + h + "): Promise already settled in state" + this.b);
            this.b = f;
            this.c = h;
            this.l()
        };
        b.prototype.l = function() {
            if (null != this.a) {
                for (var f = 0; f < this.a.length; ++f) g.b(this.a[f]);
                this.a = null
            }
        };
        var g = new c;
        b.prototype.D = function(f) {
            var h = this.f();
            f.C(h.resolve, h.reject)
        };
        b.prototype.F = function(f, h) { var k = this.f(); try { f.call(h, k.resolve, k.reject) } catch (m) { k.reject(m) } };
        b.prototype.then = function(f, h) {
            function k(w, A) { return "function" == typeof w ? function(ma) { try { m(w(ma)) } catch (na) { r(na) } } : A }
            var m, r, oa = new b(function(w, A) {
                m = w;
                r = A
            });
            this.C(k(f, m), k(h, r));
            return oa
        };
        b.prototype.catch = function(f) { return this.then(void 0, f) };
        b.prototype.C = function(f, h) {
            function k() {
                switch (m.b) {
                    case 1:
                        f(m.c);
                        break;
                    case 2:
                        h(m.c);
                        break;
                    default:
                        throw Error("Unexpected state: " +
                            m.b);
                }
            }
            var m = this;
            null == this.a ? g.b(k) : this.a.push(k)
        };
        b.resolve = d;
        b.reject = function(f) { return new b(function(h, k) { k(f) }) };
        b.race = function(f) { return new b(function(h, k) { for (var m = ba(f), r = m.next(); !r.done; r = m.next()) d(r.value).C(h, k) }) };
        b.all = function(f) {
            var h = ba(f),
                k = h.next();
            return k.done ? d([]) : new b(function(m, r) {
                function oa(ma) {
                    return function(na) {
                        w[ma] = na;
                        A--;
                        0 == A && m(w)
                    }
                }
                var w = [],
                    A = 0;
                do w.push(void 0), A++, d(k.value).C(oa(w.length - 1), r), k = h.next(); while (!k.done)
            })
        };
        return b
    });
    p("Object.is", function(a) { return a ? a : function(b, c) { return b === c ? 0 !== b || 1 / b === 1 / c : b !== b && c !== c } });
    p("Array.prototype.includes", function(a) {
        return a ? a : function(b, c) {
            var d = this;
            d instanceof String && (d = String(d));
            var e = d.length;
            c = c || 0;
            for (0 > c && (c = Math.max(c + e, 0)); c < e; c++) { var g = d[c]; if (g === b || Object.is(g, b)) return !0 }
            return !1
        }
    });
    p("String.prototype.includes", function(a) { return a ? a : function(b, c) { if (null == this) throw new TypeError("The 'this' value for String.prototype.includes must not be null or undefined"); if (b instanceof RegExp) throw new TypeError("First argument to String.prototype.includes must not be a regular expression"); return -1 !== this.indexOf(b, c || 0) } });
    var q = this || self,
        fa = /^[\w+/_-]+[=]{0,2}$/,
        ha = null;

    function ia(a) { return (a = a.querySelector && a.querySelector("script[nonce]")) && (a = a.nonce || a.getAttribute("nonce")) && fa.test(a) ? a : "" }

    function t(a) {
        a = a.split(".");
        for (var b = q, c = 0; c < a.length; c++)
            if (b = b[a[c]], null == b) return null;
        return b
    }

    function u() {}

    function ja(a) { var b = typeof a; return "object" != b ? b : a ? Array.isArray(a) ? "array" : b : "null" }

    function v(a) { return "function" == ja(a) }

    function ka(a) { var b = typeof a; return "object" == b && null != a || "function" == b }

    function la(a, b, c) { return a.call.apply(a.bind, arguments) }

    function pa(a, b, c) {
        if (!a) throw Error();
        if (2 < arguments.length) {
            var d = Array.prototype.slice.call(arguments, 2);
            return function() {
                var e = Array.prototype.slice.call(arguments);
                Array.prototype.unshift.apply(e, d);
                return a.apply(b, e)
            }
        }
        return function() { return a.apply(b, arguments) }
    }

    function x(a, b, c) { Function.prototype.bind && -1 != Function.prototype.bind.toString().indexOf("native code") ? x = la : x = pa; return x.apply(null, arguments) }

    function y(a, b) {
        a = a.split(".");
        var c = q;
        a[0] in c || "undefined" == typeof c.execScript || c.execScript("var " + a[0]);
        for (var d; a.length && (d = a.shift());) a.length || void 0 === b ? c[d] && c[d] !== Object.prototype[d] ? c = c[d] : c = c[d] = {} : c[d] = b
    }

    function z(a, b) {
        function c() {}
        c.prototype = b.prototype;
        a.prototype = new c;
        a.prototype.constructor = a
    };

    function B(a) {
        if (Error.captureStackTrace) Error.captureStackTrace(this, B);
        else {
            var b = Error().stack;
            b && (this.stack = b)
        }
        a && (this.message = String(a))
    }
    z(B, Error);
    B.prototype.name = "CustomError";

    function C(a, b) {
        this.a = a === qa && b || "";
        this.b = ra
    }
    C.prototype.K = !0;
    C.prototype.J = function() { return this.a };

    function sa(a) { return a instanceof C && a.constructor === C && a.b === ra ? a.a : "type_error:Const" }

    function D(a) { return new C(qa, a) }
    var ra = {},
        qa = {};
    var E = { g: {} };
    E.g.O = {
        X: {
            "gstatic.com": {
                loader: D("https://www.gstatic.com/charts/%{version}/loader.js"),
                debug: D("https://www.gstatic.com/charts/debug/%{version}/js/jsapi_debug_%{package}_module.js"),
                debug_i18n: D("https://www.gstatic.com/charts/debug/%{version}/i18n/jsapi_debug_i18n_%{package}_module__%{language}.js"),
                compiled: D("https://www.gstatic.com/charts/%{version}/js/jsapi_compiled_%{package}_module.js"),
                compiled_i18n: D("https://www.gstatic.com/charts/%{version}/i18n/jsapi_compiled_i18n_%{package}_module__%{language}.js"),
                css: D("https://www.gstatic.com/charts/%{version}/css/%{subdir}/%{filename}"),
                css2: D("https://www.gstatic.com/charts/%{version}/css/%{subdir1}/%{subdir2}/%{filename}"),
                third_party: D("https://www.gstatic.com/charts/%{version}/third_party/%{subdir}/%{filename}"),
                third_party2: D("https://www.gstatic.com/charts/%{version}/third_party/%{subdir1}/%{subdir2}/%{filename}"),
                third_party_gen: D("https://www.gstatic.com/charts/%{version}/third_party/%{subdir}/%{filename}")
            },
            "gstatic.cn": {
                loader: D("https://www.gstatic.cn/charts/%{version}/loader.js"),
                debug: D("https://www.gstatic.cn/charts/debug/%{version}/js/jsapi_debug_%{package}_module.js"),
                debug_i18n: D("https://www.gstatic.cn/charts/debug/%{version}/i18n/jsapi_debug_i18n_%{package}_module__%{language}.js"),
                compiled: D("https://www.gstatic.cn/charts/%{version}/js/jsapi_compiled_%{package}_module.js"),
                compiled_i18n: D("https://www.gstatic.cn/charts/%{version}/i18n/jsapi_compiled_i18n_%{package}_module__%{language}.js"),
                css: D("https://www.gstatic.cn/charts/%{version}/css/%{subdir}/%{filename}"),
                css2: D("https://www.gstatic.cn/charts/%{version}/css/%{subdir1}/%{subdir2}/%{filename}"),
                third_party: D("https://www.gstatic.cn/charts/%{version}/third_party/%{subdir}/%{filename}"),
                third_party2: D("https://www.gstatic.cn/charts/%{version}/third_party/%{subdir1}/%{subdir2}/%{filename}"),
                third_party_gen: D("https://www.gstatic.cn/charts/%{version}/third_party/%{subdir}/%{filename}")
            }
        },
        ba: ["default"],
        ca: {
            format: [],
            "default": ["format"],
            ui: ["default"],
            ui_base: ["default"],
            flashui: ["ui"],
            fw: ["ui"],
            annotatedtimeline: ["annotationchart"],
            annotationchart: ["ui", "controls", "corechart", "table"],
            areachart: "browserchart",
            bar: ["fw", "dygraph", "webfontloader"],
            barchart: "browserchart",
            browserchart: ["ui"],
            bubbles: ["fw", "d3"],
            calendar: ["fw"],
            charteditor: "ui corechart imagechart annotatedtimeline gauge motionchart orgchart table".split(" "),
            charteditor_base: "ui_base corechart imagechart annotatedtimeline gauge motionchart orgchart table_base".split(" "),
            circles: ["fw", "d3"],
            clusterchart: ["corechart", "d3"],
            columnchart: "browserchart",
            controls: ["ui"],
            controls_base: ["ui_base"],
            corechart: ["ui"],
            gantt: ["fw", "dygraph"],
            gauge: ["ui"],
            geochart: ["ui"],
            geomap: ["flashui"],
            geomap_base: ["ui_base"],
            heatmap: ["vegachart"],
            helloworld: ["fw"],
            imagechart: ["ui"],
            imageareachart: "imagechart",
            imagebarchart: "imagechart",
            imagelinechart: "imagechart",
            imagepiechart: "imagechart",
            imagesparkline: "imagechart",
            line: ["fw", "dygraph", "webfontloader"],
            linechart: "browserchart",
            map: ["ui"],
            motionchart: ["flashui"],
            orgchart: ["ui"],
            overtimecharts: ["ui", "corechart"],
            piechart: "browserchart",
            sankey: ["fw", "d3", "d3.sankey"],
            scatter: ["fw", "dygraph", "webfontloader"],
            scatterchart: "browserchart",
            sunburst: ["fw", "d3"],
            streamgraph: ["fw", "d3"],
            table: ["ui"],
            table_base: ["ui_base"],
            timeline: ["fw", "ui", "dygraph"],
            treemap: ["ui"],
            wordtree: ["ui"]
        },
        ta: { d3: { subdir1: "d3", subdir2: "v5", filename: "d3.js" }, "d3.sankey": { subdir1: "d3_sankey", subdir2: "v4", filename: "d3.sankey.js" }, webfontloader: { subdir: "webfontloader", filename: "webfont.js" } },
        sa: { dygraph: { subdir: "dygraphs", filename: "dygraph-tickers-combined.js" }, vegaLib: { subdir: "vega", filename: "vega-bundle.js" } },
        aa: {
            "default": [{ subdir: "core", filename: "tooltip.css" }],
            annotationchart: [{ subdir: "annotationchart", filename: "annotationchart.css" }],
            charteditor: [{ subdir: "charteditor", filename: "charteditor.css" }],
            charteditor_base: [{ subdir: "charteditor_base", filename: "charteditor_base.css" }],
            controls: [{ subdir: "controls", filename: "controls.css" }],
            imagesparkline: [{ subdir: "imagechart", filename: "imagesparkline.css" }],
            orgchart: [{ subdir: "orgchart", filename: "orgchart.css" }],
            table: [{ subdir: "table", filename: "table.css" }, { subdir: "util", filename: "format.css" }],
            table_base: [{ subdir: "util", filename: "format.css" }, { subdir: "table", filename: "table_base.css" }],
            ui: [{
                subdir: "util",
                filename: "util.css"
            }],
            ui_base: [{ subdir: "util", filename: "util_base.css" }]
        }
    };
    E.g.P = {
        S: {
            "chrome-frame": { versions: { "1.0.0": { uncompressed: "CFInstall.js", compressed: "CFInstall.min.js" }, "1.0.1": { uncompressed: "CFInstall.js", compressed: "CFInstall.min.js" }, "1.0.2": { uncompressed: "CFInstall.js", compressed: "CFInstall.min.js" } }, aliases: { 1: "1.0.2", "1.0": "1.0.2" } },
            swfobject: { versions: { "2.1": { uncompressed: "swfobject_src.js", compressed: "swfobject.js" }, "2.2": { uncompressed: "swfobject_src.js", compressed: "swfobject.js" } }, aliases: { 2: "2.2" } },
            "ext-core": {
                versions: {
                    "3.1.0": {
                        uncompressed: "ext-core-debug.js",
                        compressed: "ext-core.js"
                    },
                    "3.0.0": { uncompressed: "ext-core-debug.js", compressed: "ext-core.js" }
                },
                aliases: { 3: "3.1.0", "3.0": "3.0.0", "3.1": "3.1.0" }
            },
            scriptaculous: { versions: { "1.8.3": { uncompressed: "scriptaculous.js", compressed: "scriptaculous.js" }, "1.9.0": { uncompressed: "scriptaculous.js", compressed: "scriptaculous.js" }, "1.8.1": { uncompressed: "scriptaculous.js", compressed: "scriptaculous.js" }, "1.8.2": { uncompressed: "scriptaculous.js", compressed: "scriptaculous.js" } }, aliases: { 1: "1.9.0", "1.8": "1.8.3", "1.9": "1.9.0" } },
            webfont: {
                versions: {
                    "1.0.12": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.13": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.14": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.15": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.10": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.11": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.27": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.28": {
                        uncompressed: "webfont_debug.js",
                        compressed: "webfont.js"
                    },
                    "1.0.29": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.23": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.24": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.25": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.26": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.21": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.22": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.3": {
                        uncompressed: "webfont_debug.js",
                        compressed: "webfont.js"
                    },
                    "1.0.4": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.5": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.6": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.9": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.16": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.17": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.0": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.18": {
                        uncompressed: "webfont_debug.js",
                        compressed: "webfont.js"
                    },
                    "1.0.1": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.19": { uncompressed: "webfont_debug.js", compressed: "webfont.js" },
                    "1.0.2": { uncompressed: "webfont_debug.js", compressed: "webfont.js" }
                },
                aliases: { 1: "1.0.29", "1.0": "1.0.29" }
            },
            jqueryui: {
                versions: {
                    "1.8.17": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.16": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.15": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.14": {
                        uncompressed: "jquery-ui.js",
                        compressed: "jquery-ui.min.js"
                    },
                    "1.8.4": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.13": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.5": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.12": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.6": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.11": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.7": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.10": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.8": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.9": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.6.0": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.7.0": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.5.2": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.0": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.7.1": {
                        uncompressed: "jquery-ui.js",
                        compressed: "jquery-ui.min.js"
                    },
                    "1.5.3": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.1": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.7.2": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.8.2": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" },
                    "1.7.3": { uncompressed: "jquery-ui.js", compressed: "jquery-ui.min.js" }
                },
                aliases: { 1: "1.8.17", "1.5": "1.5.3", "1.6": "1.6.0", "1.7": "1.7.3", "1.8": "1.8.17", "1.8.3": "1.8.4" }
            },
            mootools: {
                versions: {
                    "1.3.0": {
                        uncompressed: "mootools.js",
                        compressed: "mootools-yui-compressed.js"
                    },
                    "1.2.1": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.1.2": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.4.0": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.3.1": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.2.2": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.4.1": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.3.2": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.2.3": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.4.2": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.2.4": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.2.5": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" },
                    "1.1.1": { uncompressed: "mootools.js", compressed: "mootools-yui-compressed.js" }
                },
                aliases: {
                    1: "1.1.2",
                    "1.1": "1.1.2",
                    "1.2": "1.2.5",
                    "1.3": "1.3.2",
                    "1.4": "1.4.2",
                    "1.11": "1.1.1"
                }
            },
            yui: {
                versions: {
                    "2.8.0r4": { uncompressed: "build/yuiloader/yuiloader.js", compressed: "build/yuiloader/yuiloader-min.js" },
                    "2.9.0": { uncompressed: "build/yuiloader/yuiloader.js", compressed: "build/yuiloader/yuiloader-min.js" },
                    "2.8.1": { uncompressed: "build/yuiloader/yuiloader.js", compressed: "build/yuiloader/yuiloader-min.js" },
                    "2.6.0": { uncompressed: "build/yuiloader/yuiloader.js", compressed: "build/yuiloader/yuiloader-min.js" },
                    "2.7.0": {
                        uncompressed: "build/yuiloader/yuiloader.js",
                        compressed: "build/yuiloader/yuiloader-min.js"
                    },
                    "3.3.0": { uncompressed: "build/yui/yui.js", compressed: "build/yui/yui-min.js" },
                    "2.8.2r1": { uncompressed: "build/yuiloader/yuiloader.js", compressed: "build/yuiloader/yuiloader-min.js" }
                },
                aliases: { 2: "2.9.0", "2.6": "2.6.0", "2.7": "2.7.0", "2.8": "2.8.2r1", "2.8.0": "2.8.0r4", "2.8.2": "2.8.2r1", "2.9": "2.9.0", 3: "3.3.0", "3.3": "3.3.0" }
            },
            prototype: {
                versions: {
                    "1.6.1.0": { uncompressed: "prototype.js", compressed: "prototype.js" },
                    "1.6.0.2": { uncompressed: "prototype.js", compressed: "prototype.js" },
                    "1.7.0.0": { uncompressed: "prototype.js", compressed: "prototype.js" },
                    "1.6.0.3": { uncompressed: "prototype.js", compressed: "prototype.js" }
                },
                aliases: { 1: "1.7.0.0", "1.6": "1.6.1.0", "1.6.0": "1.6.0.3", "1.6.1": "1.6.1.0", "1.7": "1.7.0.0", "1.7.0": "1.7.0.0" }
            },
            jquery: {
                versions: {
                    "1.2.3": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.2.6": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.3.0": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.3.1": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.3.2": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.4.0": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.4.1": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.4.2": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.4.3": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.4.4": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.5.0": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.5.1": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.5.2": {
                        uncompressed: "jquery.js",
                        compressed: "jquery.min.js"
                    },
                    "1.6.0": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.6.1": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.6.2": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.6.3": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.6.4": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.7.0": { uncompressed: "jquery.js", compressed: "jquery.min.js" },
                    "1.7.1": { uncompressed: "jquery.js", compressed: "jquery.min.js" }
                },
                aliases: {
                    1: "1.7.1",
                    "1.2": "1.2.6",
                    "1.3": "1.3.2",
                    "1.4": "1.4.4",
                    "1.5": "1.5.2",
                    "1.6": "1.6.4",
                    "1.7": "1.7.1"
                }
            },
            dojo: {
                versions: {
                    "1.3.0": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.4.0": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.3.1": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.5.0": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.4.1": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.3.2": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.2.3": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.6.0": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.5.1": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.7.0": { uncompressed: "dojo/dojo.js.uncompressed.js", compressed: "dojo/dojo.js" },
                    "1.6.1": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.4.3": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.7.1": { uncompressed: "dojo/dojo.js.uncompressed.js", compressed: "dojo/dojo.js" },
                    "1.7.2": { uncompressed: "dojo/dojo.js.uncompressed.js", compressed: "dojo/dojo.js" },
                    "1.2.0": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" },
                    "1.1.1": { uncompressed: "dojo/dojo.xd.js.uncompressed.js", compressed: "dojo/dojo.xd.js" }
                },
                aliases: {
                    1: "1.6.1",
                    "1.1": "1.1.1",
                    "1.2": "1.2.3",
                    "1.3": "1.3.2",
                    "1.4": "1.4.3",
                    "1.5": "1.5.1",
                    "1.6": "1.6.1",
                    "1.7": "1.7.2"
                }
            }
        }
    };
    var ta = Array.prototype.forEach ? function(a, b, c) { Array.prototype.forEach.call(a, b, c) } : function(a, b, c) { for (var d = a.length, e = "string" === typeof a ? a.split("") : a, g = 0; g < d; g++) g in e && b.call(c, e[g], g, a) },
        ua = Array.prototype.map ? function(a, b) { return Array.prototype.map.call(a, b, void 0) } : function(a, b) { for (var c = a.length, d = Array(c), e = "string" === typeof a ? a.split("") : a, g = 0; g < c; g++) g in e && (d[g] = b.call(void 0, e[g], g, a)); return d },
        va = Array.prototype.some ? function(a, b) { return Array.prototype.some.call(a, b, void 0) } :
        function(a, b) {
            for (var c = a.length, d = "string" === typeof a ? a.split("") : a, e = 0; e < c; e++)
                if (e in d && b.call(void 0, d[e], e, a)) return !0;
            return !1
        };

    function wa(a) { return Array.prototype.concat.apply([], arguments) }

    function xa(a) { var b = a.length; if (0 < b) { for (var c = Array(b), d = 0; d < b; d++) c[d] = a[d]; return c } return [] }

    function ya(a, b) {
        for (var c = 1; c < arguments.length; c++) {
            var d = arguments[c],
                e = ja(d);
            if ("array" == e || "object" == e && "number" == typeof d.length) {
                e = a.length || 0;
                var g = d.length || 0;
                a.length = e + g;
                for (var f = 0; f < g; f++) a[e + f] = d[f]
            } else a.push(d)
        }
    };

    function F(a, b) {
        this.a = a === za && b || "";
        this.b = Aa
    }
    F.prototype.K = !0;
    F.prototype.J = function() { return this.a.toString() };

    function Ba(a) { return a instanceof F && a.constructor === F && a.b === Aa ? a.a : "type_error:TrustedResourceUrl" }

    function Ca(a, b) {
        var c = sa(a);
        if (!Da.test(c)) throw Error("Invalid TrustedResourceUrl format: " + c);
        a = c.replace(Ea, function(d, e) {
            if (!Object.prototype.hasOwnProperty.call(b, e)) throw Error('Found marker, "' + e + '", in format string, "' + c + '", but no valid label mapping found in args: ' + JSON.stringify(b));
            d = b[e];
            return d instanceof C ? sa(d) : encodeURIComponent(String(d))
        });
        return new F(za, a)
    }
    var Ea = /%{(\w+)}/g,
        Da = /^((https:)?\/\/[0-9a-z.:[\]-]+\/|\/[^/\\]|[^:/\\%]+\/|[^:/\\%]*[?#]|about:blank#)/i,
        Fa = /^([^?#]*)(\?[^#]*)?(#[\s\S]*)?/;

    function Ga(a, b, c) {
        a = Ca(a, b);
        a = Fa.exec(Ba(a).toString());
        b = a[3] || "";
        return new F(za, a[1] + Ha("?", a[2] || "", c) + Ha("#", b, void 0))
    }
    var Aa = {};

    function Ha(a, b, c) {
        if (null == c) return b;
        if ("string" === typeof c) return c ? a + encodeURIComponent(c) : "";
        for (var d in c) {
            var e = c[d];
            e = Array.isArray(e) ? e : [e];
            for (var g = 0; g < e.length; g++) {
                var f = e[g];
                null != f && (b || (b = a), b += (b.length > a.length ? "&" : "") + encodeURIComponent(d) + "=" + encodeURIComponent(String(f)))
            }
        }
        return b
    }
    var za = {};
    var Ia = String.prototype.trim ? function(a) { return a.trim() } : function(a) { return /^[\s\xa0]*([\s\S]*?)[\s\xa0]*$/.exec(a)[1] };

    function Ja(a, b) { return a < b ? -1 : a > b ? 1 : 0 };
    var G;
    a: {
        var Ka = q.navigator;
        if (Ka) { var La = Ka.userAgent; if (La) { G = La; break a } }
        G = ""
    }

    function H(a) { return -1 != G.indexOf(a) };

    function Ma(a, b) { for (var c in a) b.call(void 0, a[c], c, a) }
    var Na = "constructor hasOwnProperty isPrototypeOf propertyIsEnumerable toLocaleString toString valueOf".split(" ");

    function Oa(a, b) { for (var c, d, e = 1; e < arguments.length; e++) { d = arguments[e]; for (c in d) a[c] = d[c]; for (var g = 0; g < Na.length; g++) c = Na[g], Object.prototype.hasOwnProperty.call(d, c) && (a[c] = d[c]) } };

    function Pa(a, b) {
        a.src = Ba(b);
        (b = a.ownerDocument && a.ownerDocument.defaultView) && b != q ? b = ia(b.document) : (null === ha && (ha = ia(q.document)), b = ha);
        b && a.setAttribute("nonce", b)
    };

    function Qa(a) { var b = Ra; return Object.prototype.hasOwnProperty.call(b, 11) ? b[11] : b[11] = a(11) };
    var Sa = H("Opera"),
        Ta = H("Trident") || H("MSIE"),
        Ua = H("Edge"),
        Va = H("Gecko") && !(-1 != G.toLowerCase().indexOf("webkit") && !H("Edge")) && !(H("Trident") || H("MSIE")) && !H("Edge"),
        Wa = -1 != G.toLowerCase().indexOf("webkit") && !H("Edge"),
        Xa;
    a: {
        var Ya = "",
            Za = function() { var a = G; if (Va) return /rv:([^\);]+)(\)|;)/.exec(a); if (Ua) return /Edge\/([\d\.]+)/.exec(a); if (Ta) return /\b(?:MSIE|rv)[: ]([^\);]+)(\)|;)/.exec(a); if (Wa) return /WebKit\/(\S+)/.exec(a); if (Sa) return /(?:Version)[ \/]?(\S+)/.exec(a) }();Za && (Ya = Za ? Za[1] : "");
        if (Ta) {
            var $a, ab = q.document;
            $a = ab ? ab.documentMode : void 0;
            if (null != $a && $a > parseFloat(Ya)) { Xa = String($a); break a }
        }
        Xa = Ya
    }
    var bb = Xa,
        Ra = {};

    function cb() {
        return Qa(function() {
            for (var a = 0, b = Ia(String(bb)).split("."), c = Ia("11").split("."), d = Math.max(b.length, c.length), e = 0; 0 == a && e < d; e++) {
                var g = b[e] || "",
                    f = c[e] || "";
                do {
                    g = /(\d*)(\D*)(.*)/.exec(g) || ["", "", "", ""];
                    f = /(\d*)(\D*)(.*)/.exec(f) || ["", "", "", ""];
                    if (0 == g[0].length && 0 == f[0].length) break;
                    a = Ja(0 == g[1].length ? 0 : parseInt(g[1], 10), 0 == f[1].length ? 0 : parseInt(f[1], 10)) || Ja(0 == g[2].length, 0 == f[2].length) || Ja(g[2], f[2]);
                    g = g[3];
                    f = f[3]
                } while (0 == a)
            }
            return 0 <= a
        })
    };

    function db(a, b) { Ma(b, function(c, d) { c && "object" == typeof c && c.K && (c = c.J()); "style" == d ? a.style.cssText = c : "class" == d ? a.className = c : "for" == d ? a.htmlFor = c : eb.hasOwnProperty(d) ? a.setAttribute(eb[d], c) : 0 == d.lastIndexOf("aria-", 0) || 0 == d.lastIndexOf("data-", 0) ? a.setAttribute(d, c) : a[d] = c }) }
    var eb = { cellpadding: "cellPadding", cellspacing: "cellSpacing", colspan: "colSpan", frameborder: "frameBorder", height: "height", maxlength: "maxLength", nonce: "nonce", role: "role", rowspan: "rowSpan", type: "type", usemap: "useMap", valign: "vAlign", width: "width" };

    function fb(a) {
        var b = document;
        a = String(a);
        "application/xhtml+xml" === b.contentType && (a = a.toLowerCase());
        return b.createElement(a)
    };

    function gb(a, b) {
        this.c = a;
        this.f = b;
        this.b = 0;
        this.a = null
    }
    gb.prototype.get = function() {
        if (0 < this.b) {
            this.b--;
            var a = this.a;
            this.a = a.next;
            a.next = null
        } else a = this.c();
        return a
    };

    function hb(a, b) {
        a.f(b);
        100 > a.b && (a.b++, b.next = a.a, a.a = b)
    };

    function ib(a) { q.setTimeout(function() { throw a; }, 0) }
    var jb;

    function kb() {
        var a = q.MessageChannel;
        "undefined" === typeof a && "undefined" !== typeof window && window.postMessage && window.addEventListener && !H("Presto") && (a = function() {
            var e = fb("IFRAME");
            e.style.display = "none";
            document.documentElement.appendChild(e);
            var g = e.contentWindow;
            e = g.document;
            e.open();
            e.close();
            var f = "callImmediate" + Math.random(),
                h = "file:" == g.location.protocol ? "*" : g.location.protocol + "//" + g.location.host;
            e = x(function(k) { if (("*" == h || k.origin == h) && k.data == f) this.port1.onmessage() }, this);
            g.addEventListener("message",
                e, !1);
            this.port1 = {};
            this.port2 = { postMessage: function() { g.postMessage(f, h) } }
        });
        if ("undefined" !== typeof a && !H("Trident") && !H("MSIE")) {
            var b = new a,
                c = {},
                d = c;
            b.port1.onmessage = function() {
                if (void 0 !== c.next) {
                    c = c.next;
                    var e = c.I;
                    c.I = null;
                    e()
                }
            };
            return function(e) {
                d.next = { I: e };
                d = d.next;
                b.port2.postMessage(0)
            }
        }
        return function(e) { q.setTimeout(e, 0) }
    };

    function lb() { this.b = this.a = null }
    var nb = new gb(function() { return new mb }, function(a) { a.reset() });
    lb.prototype.add = function(a, b) {
        var c = nb.get();
        c.set(a, b);
        this.b ? this.b.next = c : this.a = c;
        this.b = c
    };

    function ob() {
        var a = pb,
            b = null;
        a.a && (b = a.a, a.a = a.a.next, a.a || (a.b = null), b.next = null);
        return b
    }

    function mb() { this.next = this.b = this.a = null }
    mb.prototype.set = function(a, b) {
        this.a = a;
        this.b = b;
        this.next = null
    };
    mb.prototype.reset = function() { this.next = this.b = this.a = null };

    function qb(a, b) {
        rb || sb();
        tb || (rb(), tb = !0);
        pb.add(a, b)
    }
    var rb;

    function sb() {
        if (q.Promise && q.Promise.resolve) {
            var a = q.Promise.resolve(void 0);
            rb = function() { a.then(ub) }
        } else rb = function() { var b = ub;!v(q.setImmediate) || q.Window && q.Window.prototype && !H("Edge") && q.Window.prototype.setImmediate == q.setImmediate ? (jb || (jb = kb()), jb(b)) : q.setImmediate(b) }
    }
    var tb = !1,
        pb = new lb;

    function ub() {
        for (var a; a = ob();) {
            try { a.a.call(a.b) } catch (b) { ib(b) }
            hb(nb, a)
        }
        tb = !1
    };

    function vb(a) { if (!a) return !1; try { return !!a.$goog_Thenable } catch (b) { return !1 } };

    function I(a) {
        this.a = 0;
        this.j = void 0;
        this.f = this.b = this.c = null;
        this.h = this.i = !1;
        if (a != u) try {
            var b = this;
            a.call(void 0, function(c) { J(b, 2, c) }, function(c) { J(b, 3, c) })
        } catch (c) { J(this, 3, c) }
    }

    function wb() {
        this.next = this.c = this.b = this.f = this.a = null;
        this.h = !1
    }
    wb.prototype.reset = function() {
        this.c = this.b = this.f = this.a = null;
        this.h = !1
    };
    var xb = new gb(function() { return new wb }, function(a) { a.reset() });

    function yb(a, b, c) {
        var d = xb.get();
        d.f = a;
        d.b = b;
        d.c = c;
        return d
    }
    I.prototype.then = function(a, b, c) { return zb(this, v(a) ? a : null, v(b) ? b : null, c) };
    I.prototype.$goog_Thenable = !0;
    I.prototype.cancel = function(a) {
        if (0 == this.a) {
            var b = new K(a);
            qb(function() { Ab(this, b) }, this)
        }
    };

    function Ab(a, b) {
        if (0 == a.a)
            if (a.c) {
                var c = a.c;
                if (c.b) {
                    for (var d = 0, e = null, g = null, f = c.b; f && (f.h || (d++, f.a == a && (e = f), !(e && 1 < d))); f = f.next) e || (g = f);
                    e && (0 == c.a && 1 == d ? Ab(c, b) : (g ? (d = g, d.next == c.f && (c.f = d), d.next = d.next.next) : Bb(c), Cb(c, e, 3, b)))
                }
                a.c = null
            } else J(a, 3, b)
    }

    function Db(a, b) {
        a.b || 2 != a.a && 3 != a.a || Eb(a);
        a.f ? a.f.next = b : a.b = b;
        a.f = b
    }

    function zb(a, b, c, d) {
        var e = yb(null, null, null);
        e.a = new I(function(g, f) {
            e.f = b ? function(h) {
                try {
                    var k = b.call(d, h);
                    g(k)
                } catch (m) { f(m) }
            } : g;
            e.b = c ? function(h) {
                try {
                    var k = c.call(d, h);
                    void 0 === k && h instanceof K ? f(h) : g(k)
                } catch (m) { f(m) }
            } : f
        });
        e.a.c = a;
        Db(a, e);
        return e.a
    }
    I.prototype.s = function(a) {
        this.a = 0;
        J(this, 2, a)
    };
    I.prototype.u = function(a) {
        this.a = 0;
        J(this, 3, a)
    };

    function J(a, b, c) {
        if (0 == a.a) {
            a === c && (b = 3, c = new TypeError("Promise cannot resolve to itself"));
            a.a = 1;
            a: {
                var d = c,
                    e = a.s,
                    g = a.u;
                if (d instanceof I) { Db(d, yb(e || u, g || null, a)); var f = !0 } else if (vb(d)) d.then(e, g, a),
                f = !0;
                else {
                    if (ka(d)) try {
                        var h = d.then;
                        if (v(h)) {
                            Fb(d, h, e, g, a);
                            f = !0;
                            break a
                        }
                    } catch (k) {
                        g.call(a, k);
                        f = !0;
                        break a
                    }
                    f = !1
                }
            }
            f || (a.j = c, a.a = b, a.c = null, Eb(a), 3 != b || c instanceof K || Gb(a, c))
        }
    }

    function Fb(a, b, c, d, e) {
        function g(k) { h || (h = !0, d.call(e, k)) }

        function f(k) { h || (h = !0, c.call(e, k)) }
        var h = !1;
        try { b.call(a, f, g) } catch (k) { g(k) }
    }

    function Eb(a) { a.i || (a.i = !0, qb(a.l, a)) }

    function Bb(a) {
        var b = null;
        a.b && (b = a.b, a.b = b.next, b.next = null);
        a.b || (a.f = null);
        return b
    }
    I.prototype.l = function() {
        for (var a; a = Bb(this);) Cb(this, a, this.a, this.j);
        this.i = !1
    };

    function Cb(a, b, c, d) {
        if (3 == c && b.b && !b.h)
            for (; a && a.h; a = a.c) a.h = !1;
        if (b.a) b.a.c = null, Hb(b, c, d);
        else try { b.h ? b.f.call(b.c) : Hb(b, c, d) } catch (e) { Ib.call(null, e) }
        hb(xb, b)
    }

    function Hb(a, b, c) { 2 == b ? a.f.call(a.c, c) : a.b && a.b.call(a.c, c) }

    function Gb(a, b) {
        a.h = !0;
        qb(function() { a.h && Ib.call(null, b) })
    }
    var Ib = ib;

    function K(a) { B.call(this, a) }
    z(K, B);
    K.prototype.name = "cancel";
    /*
        Portions of this code are from MochiKit, received by
        The Closure Authors under the MIT license. All other code is Copyright
        2005-2009 The Closure Authors. All Rights Reserved.
       */
    function L(a, b) {
        this.h = [];
        this.F = a;
        this.D = b || null;
        this.f = this.a = !1;
        this.c = void 0;
        this.s = this.Z = this.j = !1;
        this.i = 0;
        this.b = null;
        this.l = 0
    }
    L.prototype.cancel = function(a) {
        if (this.a) this.c instanceof L && this.c.cancel();
        else {
            if (this.b) {
                var b = this.b;
                delete this.b;
                a ? b.cancel(a) : (b.l--, 0 >= b.l && b.cancel())
            }
            this.F ? this.F.call(this.D, this) : this.s = !0;
            this.a || (a = new M(this), N(this), O(this, !1, a))
        }
    };
    L.prototype.u = function(a, b) {
        this.j = !1;
        O(this, a, b)
    };

    function O(a, b, c) {
        a.a = !0;
        a.c = c;
        a.f = !b;
        Jb(a)
    }

    function N(a) {
        if (a.a) {
            if (!a.s) throw new Kb(a);
            a.s = !1
        }
    }

    function P(a, b, c, d) {
        a.h.push([b, c, d]);
        a.a && Jb(a);
        return a
    }
    L.prototype.then = function(a, b, c) {
        var d, e, g = new I(function(f, h) {
            d = f;
            e = h
        });
        P(this, d, function(f) { f instanceof M ? g.cancel() : e(f) });
        return g.then(a, b, c)
    };
    L.prototype.$goog_Thenable = !0;

    function Lb(a) { return va(a.h, function(b) { return v(b[1]) }) }

    function Jb(a) {
        if (a.i && a.a && Lb(a)) {
            var b = a.i,
                c = Mb[b];
            c && (q.clearTimeout(c.a), delete Mb[b]);
            a.i = 0
        }
        a.b && (a.b.l--, delete a.b);
        b = a.c;
        for (var d = c = !1; a.h.length && !a.j;) {
            var e = a.h.shift(),
                g = e[0],
                f = e[1];
            e = e[2];
            if (g = a.f ? f : g) try {
                var h = g.call(e || a.D, b);
                void 0 !== h && (a.f = a.f && (h == b || h instanceof Error), a.c = b = h);
                if (vb(b) || "function" === typeof q.Promise && b instanceof q.Promise) d = !0, a.j = !0
            } catch (k) { b = k, a.f = !0, Lb(a) || (c = !0) }
        }
        a.c = b;
        d && (h = x(a.u, a, !0), d = x(a.u, a, !1), b instanceof L ? (P(b, h, d), b.Z = !0) : b.then(h, d));
        c && (b =
            new Nb(b), Mb[b.a] = b, a.i = b.a)
    }

    function Ob() {
        var a = new L;
        N(a);
        O(a, !0, null);
        return a
    }

    function Kb() { B.call(this) }
    z(Kb, B);
    Kb.prototype.message = "Deferred has already fired";
    Kb.prototype.name = "AlreadyCalledError";

    function M() { B.call(this) }
    z(M, B);
    M.prototype.message = "Deferred was canceled";
    M.prototype.name = "CanceledError";

    function Nb(a) {
        this.a = q.setTimeout(x(this.c, this), 0);
        this.b = a
    }
    Nb.prototype.c = function() { delete Mb[this.a]; throw this.b; };
    var Mb = {};
    var Pb, Qb = [];

    function Rb(a, b) {
        function c() {
            var e = a.shift();
            e = Sb(e, b);
            a.length && P(e, c, c, void 0);
            return e
        }
        if (!a.length) return Ob();
        var d = Qb.length;
        ya(Qb, a);
        if (d) return Pb;
        a = Qb;
        return Pb = c()
    }

    function Sb(a, b) {
        var c = b || {};
        b = c.document || document;
        var d = Ba(a).toString(),
            e = fb("SCRIPT"),
            g = { L: e, N: void 0 },
            f = new L(Tb, g),
            h = null,
            k = null != c.timeout ? c.timeout : 5E3;
        0 < k && (h = window.setTimeout(function() {
            Ub(e, !0);
            var m = new Vb(1, "Timeout reached for loading script " + d);
            N(f);
            O(f, !1, m)
        }, k), g.N = h);
        e.onload = e.onreadystatechange = function() { e.readyState && "loaded" != e.readyState && "complete" != e.readyState || (Ub(e, c.$ || !1, h), N(f), O(f, !0, null)) };
        e.onerror = function() {
            Ub(e, !0, h);
            var m = new Vb(0, "Error while loading script " +
                d);
            N(f);
            O(f, !1, m)
        };
        g = c.attributes || {};
        Oa(g, { type: "text/javascript", charset: "UTF-8" });
        db(e, g);
        Pa(e, a);
        Wb(b).appendChild(e);
        return f
    }

    function Wb(a) { var b; return (b = (a || document).getElementsByTagName("HEAD")) && 0 != b.length ? b[0] : a.documentElement }

    function Tb() {
        if (this && this.L) {
            var a = this.L;
            a && "SCRIPT" == a.tagName && Ub(a, !0, this.N)
        }
    }

    function Ub(a, b, c) {
        null != c && q.clearTimeout(c);
        a.onload = u;
        a.onerror = u;
        a.onreadystatechange = u;
        b && window.setTimeout(function() { a && a.parentNode && a.parentNode.removeChild(a) }, 0)
    }

    function Vb(a, b) {
        var c = "Jsloader error (code #" + a + ")";
        b && (c += ": " + b);
        B.call(this, c);
        this.code = a
    }
    z(Vb, B);
    E.g.m = {};
    var Xb = Sb,
        Zb = Yb;

    function $b(a) { return Ga(a.format, a.H, a.V || {}) }

    function Yb(a, b, c) {
        c = c || {};
        a = Ga(a, b, c);
        var d = Xb(a, { timeout: 3E4, attributes: { async: !1, defer: !1 } });
        return new Promise(function(e) { P(d, e, null, void 0) })
    }
    E.g.m.oa = function(a) { Yb = a };
    E.g.m.ra = function(a) { Xb = a };
    E.g.m.R = $b;
    E.g.m.load = Zb;
    E.g.m.ia = function(a) {
        a = ua(a, $b);
        if (0 == a.length) return Promise.resolve();
        var b = { timeout: 3E4, attributes: { async: !1, defer: !1 } },
            c = [];
        !Ta || cb() ? ta(a, function(d) { c.push(Xb(d, b)) }) : c.push(Rb(a, b));
        return Promise.all(ua(c, function(d) { return new Promise(function(e) { return P(d, e, null, void 0) }) }))
    };
    E.g.m.ka = function(a, b, c) { return { format: a, H: b, V: c } };
    E.g.o = {};
    var Q = {};
    E.g.o.da = function(a) { return Q[a] && Q[a].loaded };
    E.g.o.ea = function(a) { return Q[a] && Q[a].W };
    E.g.o.T = function() {
        return new Promise(function(a) {
            "undefined" == typeof window || "complete" === document.readyState ? a() : window.addEventListener ? (document.addEventListener("DOMContentLoaded", a, !0), window.addEventListener("load", a, !0)) : window.attachEvent ? window.attachEvent("onload", a) : v(window.onload) ? window.onload = function(b) {
                window.onload(b);
                a()
            } : window.onload = a
        })
    };
    E.g.o.ja = Q;
    E.g.o.na = function() { Q = {} };
    E.g.o.pa = function(a) {
        Q[a] || (Q[a] = { loaded: !1 });
        Q[a].loaded = !0
    };
    E.g.o.qa = function(a, b) { Q[a] = { W: b, loaded: !1 } };
    E.g.G = { 1: "1.0", "1.0": "current", "1.1": "upcoming", "1.2": "testing", 41: "pre-45", 42: "pre-45", 43: "pre-45", 44: "pre-45", 46: "46.1", "46.1": "46.2", 48: "48.1", current: "48", upcoming: "48", testing: "48" };

    function ac(a, b) {
        this.b = {};
        this.a = [];
        this.c = 0;
        var c = arguments.length;
        if (1 < c) { if (c % 2) throw Error("Uneven number of arguments"); for (var d = 0; d < c; d += 2) this.set(arguments[d], arguments[d + 1]) } else if (a)
            if (a instanceof ac)
                for (c = a.v(), d = 0; d < c.length; d++) this.set(c[d], a.get(c[d]));
            else
                for (d in a) this.set(d, a[d])
    }
    l = ac.prototype;
    l.A = function() { bc(this); for (var a = [], b = 0; b < this.a.length; b++) a.push(this.b[this.a[b]]); return a };
    l.v = function() { bc(this); return this.a.concat() };

    function bc(a) {
        if (a.c != a.a.length) {
            for (var b = 0, c = 0; b < a.a.length;) {
                var d = a.a[b];
                R(a.b, d) && (a.a[c++] = d);
                b++
            }
            a.a.length = c
        }
        if (a.c != a.a.length) {
            var e = {};
            for (c = b = 0; b < a.a.length;) d = a.a[b], R(e, d) || (a.a[c++] = d, e[d] = 1), b++;
            a.a.length = c
        }
    }
    l.get = function(a, b) { return R(this.b, a) ? this.b[a] : b };
    l.set = function(a, b) {
        R(this.b, a) || (this.c++, this.a.push(a));
        this.b[a] = b
    };
    l.forEach = function(a, b) {
        for (var c = this.v(), d = 0; d < c.length; d++) {
            var e = c[d],
                g = this.get(e);
            a.call(b, g, e, this)
        }
    };

    function R(a, b) { return Object.prototype.hasOwnProperty.call(a, b) };
    var cc = /^(?:([^:/?#.]+):)?(?:\/\/(?:([^\\/?#]*)@)?([^\\/?#]*?)(?::([0-9]+))?(?=[\\/?#]|$))?([^?#]+)?(?:\?([^#]*))?(?:#([\s\S]*))?$/;

    function dc(a, b) {
        if (a) {
            a = a.split("&");
            for (var c = 0; c < a.length; c++) {
                var d = a[c].indexOf("="),
                    e = null;
                if (0 <= d) {
                    var g = a[c].substring(0, d);
                    e = a[c].substring(d + 1)
                } else g = a[c];
                b(g, e ? decodeURIComponent(e.replace(/\+/g, " ")) : "")
            }
        }
    };

    function S(a) {
        this.a = this.j = this.f = "";
        this.l = null;
        this.h = this.b = "";
        this.i = !1;
        var b;
        a instanceof S ? (this.i = a.i, ec(this, a.f), this.j = a.j, this.a = a.a, fc(this, a.l), this.b = a.b, gc(this, hc(a.c)), this.h = a.h) : a && (b = String(a).match(cc)) ? (this.i = !1, ec(this, b[1] || "", !0), this.j = T(b[2] || ""), this.a = T(b[3] || "", !0), fc(this, b[4]), this.b = T(b[5] || "", !0), gc(this, b[6] || "", !0), this.h = T(b[7] || "")) : (this.i = !1, this.c = new U(null, this.i))
    }
    S.prototype.toString = function() {
        var a = [],
            b = this.f;
        b && a.push(V(b, ic, !0), ":");
        var c = this.a;
        if (c || "file" == b) a.push("//"), (b = this.j) && a.push(V(b, ic, !0), "@"), a.push(encodeURIComponent(String(c)).replace(/%25([0-9a-fA-F]{2})/g, "%$1")), c = this.l, null != c && a.push(":", String(c));
        if (c = this.b) this.a && "/" != c.charAt(0) && a.push("/"), a.push(V(c, "/" == c.charAt(0) ? jc : kc, !0));
        (c = this.c.toString()) && a.push("?", c);
        (c = this.h) && a.push("#", V(c, lc));
        return a.join("")
    };
    S.prototype.resolve = function(a) {
        var b = new S(this),
            c = !!a.f;
        c ? ec(b, a.f) : c = !!a.j;
        c ? b.j = a.j : c = !!a.a;
        c ? b.a = a.a : c = null != a.l;
        var d = a.b;
        if (c) fc(b, a.l);
        else if (c = !!a.b) {
            if ("/" != d.charAt(0))
                if (this.a && !this.b) d = "/" + d;
                else { var e = b.b.lastIndexOf("/"); - 1 != e && (d = b.b.substr(0, e + 1) + d) }
            e = d;
            if (".." == e || "." == e) d = "";
            else if (-1 != e.indexOf("./") || -1 != e.indexOf("/.")) {
                d = 0 == e.lastIndexOf("/", 0);
                e = e.split("/");
                for (var g = [], f = 0; f < e.length;) {
                    var h = e[f++];
                    "." == h ? d && f == e.length && g.push("") : ".." == h ? ((1 < g.length || 1 == g.length &&
                        "" != g[0]) && g.pop(), d && f == e.length && g.push("")) : (g.push(h), d = !0)
                }
                d = g.join("/")
            } else d = e
        }
        c ? b.b = d : c = "" !== a.c.toString();
        c ? gc(b, hc(a.c)) : c = !!a.h;
        c && (b.h = a.h);
        return b
    };

    function ec(a, b, c) {
        a.f = c ? T(b, !0) : b;
        a.f && (a.f = a.f.replace(/:$/, ""))
    }

    function fc(a, b) {
        if (b) {
            b = Number(b);
            if (isNaN(b) || 0 > b) throw Error("Bad port number " + b);
            a.l = b
        } else a.l = null
    }

    function gc(a, b, c) { b instanceof U ? (a.c = b, mc(a.c, a.i)) : (c || (b = V(b, nc)), a.c = new U(b, a.i)) }

    function T(a, b) { return a ? b ? decodeURI(a.replace(/%25/g, "%2525")) : decodeURIComponent(a) : "" }

    function V(a, b, c) { return "string" === typeof a ? (a = encodeURI(a).replace(b, oc), c && (a = a.replace(/%25([0-9a-fA-F]{2})/g, "%$1")), a) : null }

    function oc(a) { a = a.charCodeAt(0); return "%" + (a >> 4 & 15).toString(16) + (a & 15).toString(16) }
    var ic = /[#\/\?@]/g,
        kc = /[#\?:]/g,
        jc = /[#\?]/g,
        nc = /[#\?@]/g,
        lc = /#/g;

    function U(a, b) {
        this.b = this.a = null;
        this.c = a || null;
        this.f = !!b
    }

    function W(a) { a.a || (a.a = new ac, a.b = 0, a.c && dc(a.c, function(b, c) { a.add(decodeURIComponent(b.replace(/\+/g, " ")), c) })) }
    l = U.prototype;
    l.add = function(a, b) {
        W(this);
        this.c = null;
        a = X(this, a);
        var c = this.a.get(a);
        c || this.a.set(a, c = []);
        c.push(b);
        this.b += 1;
        return this
    };

    function pc(a, b) {
        W(a);
        b = X(a, b);
        R(a.a.b, b) && (a.c = null, a.b -= a.a.get(b).length, a = a.a, R(a.b, b) && (delete a.b[b], a.c--, a.a.length > 2 * a.c && bc(a)))
    }

    function qc(a, b) {
        W(a);
        b = X(a, b);
        return R(a.a.b, b)
    }
    l.forEach = function(a, b) {
        W(this);
        this.a.forEach(function(c, d) { ta(c, function(e) { a.call(b, e, d, this) }, this) }, this)
    };
    l.v = function() {
        W(this);
        for (var a = this.a.A(), b = this.a.v(), c = [], d = 0; d < b.length; d++)
            for (var e = a[d], g = 0; g < e.length; g++) c.push(b[d]);
        return c
    };
    l.A = function(a) {
        W(this);
        var b = [];
        if ("string" === typeof a) qc(this, a) && (b = wa(b, this.a.get(X(this, a))));
        else { a = this.a.A(); for (var c = 0; c < a.length; c++) b = wa(b, a[c]) }
        return b
    };
    l.set = function(a, b) {
        W(this);
        this.c = null;
        a = X(this, a);
        qc(this, a) && (this.b -= this.a.get(a).length);
        this.a.set(a, [b]);
        this.b += 1;
        return this
    };
    l.get = function(a, b) {
        if (!a) return b;
        a = this.A(a);
        return 0 < a.length ? String(a[0]) : b
    };
    l.toString = function() {
        if (this.c) return this.c;
        if (!this.a) return "";
        for (var a = [], b = this.a.v(), c = 0; c < b.length; c++) {
            var d = b[c],
                e = encodeURIComponent(String(d));
            d = this.A(d);
            for (var g = 0; g < d.length; g++) {
                var f = e;
                "" !== d[g] && (f += "=" + encodeURIComponent(String(d[g])));
                a.push(f)
            }
        }
        return this.c = a.join("&")
    };

    function hc(a) {
        var b = new U;
        b.c = a.c;
        a.a && (b.a = new ac(a.a), b.b = a.b);
        return b
    }

    function X(a, b) {
        b = String(b);
        a.f && (b = b.toLowerCase());
        return b
    }

    function mc(a, b) {
        b && !a.f && (W(a), a.c = null, a.a.forEach(function(c, d) {
            var e = d.toLowerCase();
            d != e && (pc(this, d), pc(this, e), 0 < c.length && (this.c = null, this.a.set(X(this, e), xa(c)), this.b += c.length))
        }, a));
        a.f = b
    };
    E.g.B = {};
    var rc, Y, sc = null,
        tc;

    function uc() {
        sc = Y = rc = null;
        t("google.load") || (y("google.load", vc), y("google.setOnLoadCallback", E.M));
        var a = document.getElementsByTagName("script");
        a = a[a.length - 1].getAttribute("src");
        a = new S(a);
        var b = a.a;
        tc = b = b.match(/^www\.gstatic\.cn/) ? "gstatic.cn" : "gstatic.com";
        wc(a)
    }

    function wc(a) {
        a = new U(a.c.toString());
        var b = a.get("callback");
        "string" === typeof b && (b = Z(b), E.g.o.T().then(b));
        a = a.get("autoload");
        if ("string" === typeof a) try {
            if ("" !== a) {
                var c = JSON.parse(a).modules;
                for (a = 0; a < c.length; a++) {
                    var d = c[a];
                    vc(d.name, d.version, d)
                }
            }
        } catch (e) { throw Error("Autoload failed with: " + e); }
    }

    function xc(a) {
        var b = a,
            c, d = a.match(/^testing-/);
        d && (b = b.replace(/^testing-/, ""));
        a = b;
        do {
            if (b === E.g.G[b]) throw Error("Infinite loop in version mapping: " + b);
            (c = E.g.G[b]) && (b = c)
        } while (c);
        c = (d ? "testing-" : "") + b;
        return { version: "pre-45" == b ? a : c, U: c }
    }

    function yc(a) {
        var b = E.g.O.X[tc].loader,
            c = xc(a);
        return E.g.m.load(b, { version: c.U }).then(function() {
            var d = t("google.charts.loader.VersionSpecific.load") || t("google.charts.loader.publicLoad") || t("google.charts.versionSpecific.load");
            if (!d) throw Error("Bad version: " + a);
            sc = function(e) {
                e = d(c.version, e);
                if (null == e || null == e.then) {
                    var g = t("google.charts.loader.publicSetOnLoadCallback") || t("google.charts.versionSpecific.setOnLoadCallback");
                    e = new Promise(function(f) { g(f) });
                    e.then = g
                }
                return e
            }
        })
    }

    function zc(a, b) {
        b.domain = tc;
        b.callback = Z(b.callback);
        if (!rc) {
            if (b.enableUrlSettings && window.URLSearchParams) try { a = (new URLSearchParams(top.location.search)).get("charts-version") || a } catch (c) { console.info("Failed to get charts-version from top URL", c) }
            rc = yc(a)
        }
        return Y = rc.then(function() { return sc(b) })
    }
    E.Y = function(a) { return E.load(Object.assign({}, a, { safeMode: !0 })) };
    y("google.charts.safeLoad", E.Y);
    E.load = function(a) {
        for (var b = [], c = 0; c < arguments.length; ++c) b[c] = arguments[c];
        c = 0;
        "visualization" === b[c] && c++;
        var d = "current";
        if ("string" === typeof b[c] || "number" === typeof b[c]) d = String(b[c]), c++;
        var e = {};
        ka(b[c]) && (e = b[c]);
        return zc(d, e)
    };
    y("google.charts.load", E.load);
    E.M = function(a) { if (!Y) throw Error("Must call google.charts.load before google.charts.setOnLoadCallback"); return a ? Y.then(a) : Y };
    y("google.charts.setOnLoadCallback", E.M);
    var Ac = D("https://maps.googleapis.com/maps/api/js?jsapiRedirect=true"),
        Bc = D("https://maps-api-ssl.google.com/maps?jsapiRedirect=true&file=googleapi");

    function Cc(a, b, c) {
        console.warn("Loading Maps API with the jsapi loader is deprecated.");
        c = c || {};
        a = c.key || c.client;
        var d = c.libraries,
            e = function(h) {
                for (var k = {}, m = 0; m < h.length; m++) {
                    var r = h[m];
                    k[r[0]] = r[1]
                }
                return k
            }(c.other_params ? c.other_params.split("&").map(function(h) { return h.split("=") }) : []),
            g = Object.assign({}, { key: a, ha: d }, e),
            f = "2" === b ? Bc : Ac;
        Y = new Promise(function(h) {
            var k = Z(c && c.callback);
            E.g.m.load(f, {}, g).then(k).then(h)
        })
    }
    var Dc = D("https://www.gstatic.com/inputtools/js/ita/inputtools_3.js");

    function Ec(a, b, c) { ka(c) && c.packages ? (Array.isArray(c.packages) ? c.packages : [c.packages]).includes("inputtools") ? (console.warn("Loading Input Tools with the jsapi loader is deprecated.\nPlease load " + (Dc + " directly.")), a = Z(c.callback), E.g.m.load(Dc, {}).then(a)) : console.error("Loading elements other than inputtools with the jsapi loader is unsupported.") : console.error("google.load of elements was invoked without specifying packages") }
    var Fc = D("https://ajax.googleapis.com/ajax/libs/%{module}/%{version}/%{file}");

    function Gc(a, b) {
        var c;
        do {
            if (a === b[a]) throw Error("Infinite loop in version mapping for version " + a);
            (c = b[a]) && (a = c)
        } while (c);
        return a
    }

    function Hc(a, b, c) {
        var d = E.g.P.S[a];
        if (d) {
            b = Gc(b, d.aliases);
            d = d.versions[b];
            if (!d) throw Error("Unknown version, " + b + ", of " + a + ".");
            var e = { module: a, version: b || "", file: d.compressed };
            b = Ba(E.g.m.R({ format: Fc, H: e })).toString();
            console.warn("Loading modules with the jsapi loader is deprecated.\nPlease load " + (a + " directly from " + b + "."));
            Y = new Promise(function(g) {
                var f = Z(c && c.callback);
                E.g.m.load(Fc, e).then(f).then(g)
            })
        } else setTimeout(function() { throw Error('Module "' + a + '" is not supported.'); }, 0)
    }

    function Z(a) {
        return function() {
            if ("function" === typeof a) a();
            else if ("string" === typeof a && "" !== a) try {
                var b = t(a);
                if ("function" !== typeof b) throw Error("Type of '" + a + "' is " + typeof b + ".");
                b()
            } catch (c) { throw Error("Callback of " + a + " failed with: " + c); }
        }
    }

    function vc(a) {
        for (var b = [], c = 0; c < arguments.length; ++c) b[c] = arguments[c];
        switch (b[0]) {
            case "maps":
                Cc.apply(null, n(b));
                break;
            case "elements":
                Ec.apply(null, n(b));
                break;
            case "visualization":
                E.load.apply(E, n(b));
                break;
            default:
                Hc.apply(null, n(b))
        }
    }
    y("google.loader.LoadFailure", !1);
    tc ? console.warn("Google Charts loader.js should only be loaded once.") : uc();
    E.g.B.ga = uc;
    E.g.B.la = xc;
    E.g.B.ma = wc;
    E.g.B.fa = function() { return sc };
}).call(this);