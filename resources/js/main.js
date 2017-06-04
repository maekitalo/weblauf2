requirejs.config({
    baseUrl: 'js',
    paths: {
        'jquery': 'jquery-3.2.1',
        'datatables.net': '../DataTables-1.10.15/media/js/jquery.dataTables',
        'datatables.select': '../Select-1.2.2/js/dataTables.select',
        'datatables.select': '../DataTables-1.10.15/extensions/Select/js/dataTables.select',
        'datatables.fixedcolumns': '../DataTables-1.10.15/extensions/FixedColumns/js/dataTables.fixedColumns',
        'jqueryUi': '../jquery-ui-1.12.1.custom/jquery-ui',
        'noty': 'noty/packaged/jquery.noty.packaged'
    }
})

requirejs(['jquery'], function($) {

    $('#nav a').click(function(ev) {
        ev.preventDefault();
        requirejs([$(this).attr('href')], function(screen) {
            screen.onLoad();
        })
    })

    $("#nav li:has(ul)").hover(function(){
        $(this).find("ul").slideDown();
    }, function(){
        $(this).find("ul").hide();
    });
});
