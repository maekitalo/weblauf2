define(['jquery', 'veranstaltung', 'wettkampf'], function($, veranstaltung, wettkampf) {
    var my = {}

    my.onLoad = function() {
        if (!veranstaltung.wid)
            return;

        $('#content').load('html/wertung.html', {},
            function() {
                $.getJSON('wettkaempfe.json', { vid: veranstaltung.vid }, function(data) {
                    var sel = $('#wettkampf');
                    $.each(data, function (wid, wer) {
                        $('<option>').val(wer.wid).text(wer.name).appendTo(sel);
                    });

                    sel.val(veranstaltung.wid)
                       .change(function(ev) {
                            veranstaltung.selectWettkampf(
                                $(this).val(), function() {
                                    my.table.ajax.reload();
                                });
                        });
                });

                my.table = $('#wertungenTable').DataTable({
                    ajax: {
                        url: 'wertungen.json',
                        data: function() { return { vid: veranstaltung.vid, wid: veranstaltung.wid } },
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'rid' },
                        { data: 'name' },
                        { data: 'abhaengig',
                          render: function(data, type, row, meta) {
                                return row.aw ? row.aw.name : ''; }
                        },
                        { data: 'urkunde' },
                        { data: 'preis' }
                    ],
                    order: [0, 'asc']
                });

                my.table.on('click', 'tr', function () {
                    var wertung = my.table.row(this).data();
                    veranstaltung.selectWertung(wertung);
                });
            });
    }

    return my;
})
