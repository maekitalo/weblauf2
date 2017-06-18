define(['utils', 'jquery'], function(utils) {

    var my = []

    $.fn.wettkampf = function(cb) {
        var sel = $(this);
        $.getJSON(
            'wettkaempfe.json',
            { vid: my.vid },
            function(data) {
                $.each(data, function (wid, wer) {
                    $('<option>').val(wer.wid).text(wer.name).appendTo(sel);
                });
                if (cb)
                    cb(sel);
            }
        );

        return this;
    }

    $.fn.wertung = function(cb) {
        var sel = $(this);
        $.getJSON(
            'wertungen.json',
            { vid: my.vid, wid: my.wid },
            function(data) {
                $.each(data, function (rid, wet) {
                    $('<option>').val(wet.rid).text(wet.name).appendTo(sel);
                });
                if (cb)
                    cb(sel);
            }
        );

        return this;
    }

    my.selectVeranstaltung = function(veranstaltung, cb) {
        if (!veranstaltung) {
            my.veranstaltung = null;
            my.vid = null;
            my.selectWettkampf(null, cb);
        }
        else if ($.isNumeric(veranstaltung)) {
            $.getJSON('veranstaltung.json', { vid: veranstaltung },
                function (v) { my.selectVeranstaltung(v, cb); });
        }
        else if (my.vid !== veranstaltung.vid)
        {
            my.veranstaltung = veranstaltung;
            my.vid = veranstaltung.vid;
            my.wid = null;
            my.rid = null;
            my.wettkampf = null;
            my.wertung = null;
            document.title = veranstaltung.name;
            utils.information('Veranstaltung <i>' + veranstaltung.name + '</i> ausgewählt');
            if (cb)
                cb(wettkampf);
        }
    }

    my.selectWettkampf = function(wettkampf, cb) {
        if (!wettkampf)
        {
            my.wettkampf = null;
            my.wid = null;
            my.selectWertung(null, cb);
        }
        else if ($.isNumeric(wettkampf)) {
            $.getJSON('wettkampf.json', { vid: my.vid, wid: wettkampf },
                function (w) { my.selectWettkampf(w, cb); });
        }
        else if (my.wid !== wettkampf.wid) {
            my.wettkampf = wettkampf;
            my.wid = wettkampf.wid;
            my.selectWertung(null);
            utils.information('Wettkampf <i>' + wettkampf.name + '</i> ausgewählt');
            if (cb)
                cb(wettkampf);
        }
    }

    my.selectWertung = function(wertung, cb) {
        if (!wertung)
        {
            my.wertung = null;
            my.rid = null;
            if (cb)
                cb();
        }
        else if ($.isNumeric(wertung)) {
            $.getJSON('wertung.json', { vid: my.vid, wid: my.wid, rid: wertung },
                function(w)  { my.selectWertung(w, cb) });
        }
        else if (my.rid !== wertung.rid) {
            my.wertung = wertung;
            my.rid = wertung.rid;
            utils.information('Wertung <i>' + wertung.name + '</i> ausgewählt');
            if (cb)
                cb(wertung);
        }
    }

    my.goToScreen = function(screen) {
        requirejs(
            [screen],
            function(screen) {
                screen.onLoad();
            },
            function(err) {
                my.error(err.toString());
            })
    }

    return my;
})
