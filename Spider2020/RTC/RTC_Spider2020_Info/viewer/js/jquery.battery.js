(function($) {
 
    $.fn.battery = function(options) {
        var maxVal = 100;
        var settings = $.extend({
            batteryColor:    "#61c419",
            backgroundColor: "lightgrey",
            textColor:       "#000",
            maxWidth: 150,
        }, options);

        var element = this;
        this.append('<div class="batteryBody"><div class="batteryFill"></div></div><div class="batteryTerminal"></div>');

        function showBattery(currentVal, targetVal)
        {
            var targetWidth = ((settings.maxWidth/maxVal)*targetVal).toFixed(2);
            var currentPercent = ((currentVal/targetVal)*100).toFixed(0);
            var fill = $(".batteryFill", element);
            fill.width(targetWidth);
            fill.css("background-image", createGradient(settings.batteryColor, settings.backgroundColor, currentPercent));
            var textElement = '<div class="batteryText">'+currentVal+'%</div>';
            fill.html(textElement);
            $(".batteryText", element).css("color", settings.textColor);
        }

        function createGradient(primaryColor, secondaryColor, percentage){
            var gradient = "linear-gradient(to right, {primaryColor} 0%, {primaryColor} {percentage}%, {secondaryColor} {percentage}% , {secondaryColor} 100%)";
            gradient = replace(gradient, "{primaryColor}", primaryColor);
            gradient = replace(gradient, "{secondaryColor}", secondaryColor);
            gradient = replace(gradient, "{percentage}", percentage);
            return gradient;
        }

        function replace(text, what, value){
            return text.replace(new RegExp(what, 'g'), value);
        }

        var update  = function(value, options = {}) {
            $.extend(settings, options);
            showBattery(value, maxVal);
            return element;
        }

        showBattery(0, maxVal);

        return {
            update: update,
        }
    };
 
}(jQuery));