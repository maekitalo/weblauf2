define(['jquery', 'veranstaltung', 'utils', 'datatables.net', 'datatables.select', 'jquery-ui', 'populate'], function($, veranstaltung, utils) {
    var my = {}

    my.onLoad = function() {
        if (!veranstaltung.vid)
            return;

        $('#content').load('html/wettkampf.html', {},
            function() {
                my.table = $('#wettkaempfeTable').DataTable({
                    ajax: {
                        url: 'wettkaempfe.json',
                        data: { vid: veranstaltung.vid },
                        dataSrc: ''
                    },
                    select: true,
                    columns: [
                        { data: 'wid' },
                        { data: 'name' },
                        { data: 'art' },
                        { data: 'staVon' },
                        { data: 'staBis' },
                        { data: 'startzeit' }
                    ],
                    order: [ [5, 'asc'], [0, 'asc'] ]
                });

                my.table.on('click', 'tr', function () {
                    var wettkampf = my.table.row(this).data();
                    veranstaltung.selectWettkampf(wettkampf);
                });

                $('#bearbeiten').click(function() {
                    var data = my.table.rows({selected:true}).data();
                    var wettkampf = data.length > 0 ? data[0] : my.wettkampf;

                    if (!wettkampf)
                    {
                        utils.error('keine Wertung ausgewählt', 5000);
                        return;
                    }

                    $('<div/>').load('html/wettkampf/edit.html', function() {
                        $(this).populate(wettkampf)
                               .dialog({
                                    buttons: [
                                        {
                                            text: 'Ok',
                                            click: function() {
                                                utils.action('savewettkampf', $('form', $(this)).serialize());
                                                $(this).remove();
                                                my.table.ajax.reload();
                                            }
                                        },
                                        {
                                            text: 'cancel',
                                            click: function() {
                                                $(this).remove();
                                            }
                                        }
                                    ]
                               })
                    })
                });
            });
    }

    return my;
})
