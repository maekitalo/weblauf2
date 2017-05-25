requirejs.config({
    baseUrl: 'js',
    paths: {
        'jquery': 'jquery-3.2.1',
        'datatables.net': '../DataTables-1.10.15/media/js/jquery.dataTables',
        'datatables.select': '../Select-1.2.2/js/dataTables.select',
        'datatables.fixedcolumns': '../FixedColumns-3.2.2/js/dataTables.fixedColumns',
        'jqueryUi': '../jquery-ui-1.12.1.custom/jquery-ui',
    }
})

requirejs(['jquery'], function($) {

    $('#nav a').click(function(ev) {
        ev.preventDefault();
        requirejs([$(this).attr('href')], function(screen) {
            screen.onLoad();
        })
    })
});
