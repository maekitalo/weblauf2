define(['jquery'], function() {

    $.fn.populate = function(values) {
        $(':input', $(this)).each(function(idx, elem) {
            $(elem).val(values[elem.name]);
        });

        return this;
    }
})
