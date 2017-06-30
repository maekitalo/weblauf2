define(['jquery'], function() {
    $.fn.getOptions = function(url, p1, p2) {

        var cb;
        var addempty;

        if ($.isFunction(p1)) {
            addempty = true;
            cb = p1;
        }
        else {
            addempty = p1;
            cb = p2;
        }

        var element = this;

        $.getJSON(url, {}, function(values) {
            if (addempty == null || addempty) {
                $('<option>', {}).appendTo(element);
            }

            $.each(values, function(i, item) {

                if ($.isPlainObject(item) {
                    $('<option>', item).appendTo(element);
                }
                else {
                    $('<option>', {
                        value: item,
                        html: item
                    }).appendTo(element);
                }
            }

            if ($.isFunction(db))
                cb(this);
        }
    }
})
