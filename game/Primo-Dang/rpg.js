RPG = {
    Cenarios: {
        ReinosFerro: {
            etnias: {
                cygnaranos: {
                    caspianos_povos_meio: {
                    },
                    morridanos_thurianos: {
                        nomes: {
                            masculinos: ['Aidan', 'Ardan', 'Bastian', 'Blake', 'Bradig', 'Branduff', 'Brogan', 'Brosnan', 'Byrleigh', 'Cagneigh', 'Colm', 'Conleth', 'Conor', 'Cormick', 'Cronan', 'Cullin', 'Darian', 'Darragh', 'Decklan', 'Deegan', 'Dermid', 'Dermot', 'Dougal', 'Oougan', 'Durgan', 'Eilish', 'Fergus', 'Finnegan', 'Flynn', 'Gervin', 'Gorman', 'Gralan', 'Hagan', 'Hanagan', 'Hogan', 'Ian', 'Keegan', 'Killian', 'Kirwin', 'Larkin', 'Lonan', 'Lorcan', 'Lorgan', 'Luan', 'Mairtin', 'Morgan', 'Nolan', 'Odran', 'Olan', 'Ossian', 'Piran', 'Quinn', 'Quinlan', 'Rogan', 'Ronan', 'Ryleigh'],
                            femininos: ['Aideen', 'Ansleigh', 'Beara', 'Boand', 'Brennan', 'Caelan', 'Caitlin', 'Carleigh', 'Carolan', 'Clancy', 'Dana', 'Devlin', 'Eithne', 'Evlin', 'Gillian', 'Jelyan', 'Jerilyn', 'Kaelin', 'Keehan', 'Kennan', 'Kenseigh', 'Kerin', 'Kerry', 'Kileigh', 'Lacy', 'Leigan', 'Lennon', 'Mara', 'Meara', 'Megan', 'Milish', 'Niall', 'Nivin', 'Paddy', 'Regan', 'Roshean', 'Shannon', 'Teagan', 'Tiernan']
                        },
                        sobrenomes: ['Aghamore', 'Bain', 'Bartley', 'Beene', 'Berrigan', 'Blathmac', 'Bradigan', 'Bray', 'Brenn', 'Burney', 'Byme', 'Carrock', 'Cathmore', 'Corcoran', 'CorIey', 'Cronan', 'Decklan', 'Deorain', 'Derrigan', 'Donovan', 'Doyle', 'Dromore', 'Duff', 'Duffock', 'Duggan', 'Dunne', 'Enabarr', 'Fagan', 'Finnian', 'Finnigan', 'Gafneagh', 'Garrity', 'Gilmore', 'Glasneagh', 'Gormleigh', 'Gowan', 'Grady', 'Grath', 'Hugh', 'Hurlough', 'Kaddock', 'Kain', 'Kannock', 'Kavanaugh', 'Kearneigh', 'Keehan', 'Kerrigan', 'Kilbride', 'Kildair', 'Lattimore', 'Leegan', 'Lochlan', 'Lowreigh', 'Lynch', 'Madigan', 'Melroane', 'Moriarty', 'Murrough', 'Rathleagh', 'Reardan', 'Riordan', 'Roane', 'Ryland', 'Scully', 'Sheridan', 'Sorleagh', 'Torcail', 'Turlough', 'Vain', 'Waddock', 'Wain']
                    }
                }
            }
        }
    },
    Util: {}
};

ReinosFerro = RPG.Cenarios.ReinosFerro;
RF = ReinosFerro;


RPG.init = function(){
    console.log('Acesse o objeto RPG');

    RPG.carregarSinonimos();
};

RPG.carregarSinonimos = function () {
    var RF_etnias = ReinosFerro.etnias;
    var cygnaranos = RF_etnias.cygnaranos;
    cygnaranos.caspianos = cygnaranos.caspianos_povos_meio;
    cygnaranos.povos_meio = cygnaranos.caspianos_povos_meio;
    cygnaranos.morridanos = cygnaranos.morridanos_thurianos;
    cygnaranos.thurianos = cygnaranos.morridanos_thurianos;
};

RPG.Util.getRand = function(arr) {
    return arr[Math.floor(Math.random() * arr.length)];
};

RPG.gerarNome = function(nomes, sobrenomes) {
    return RPG.Util.getRand(nomes) + ' ' + RPG.Util.getRand(sobrenomes);
};

RF.gerarNome = function (etnia, genero) {
    var RF_etnias = ReinosFerro.etnias;
    var nomes = new JefNode(RF_etnias).filter(function(node) {
        if (
            $.isArray(node.value)
            && (
                !etnia
                || $.inArray(etnia, [node.key, node.parent.parent.key, node.parent.parent.parent.key]) > -1
            ) && (
                !$.isEmptyObject(node.value) node.key === 'nomes'
                || !genero
                || ($.inArray(genero.toLowerCase(), ['masculinos', 'masculino', 'm', 'masc', 'homem', 'homens']) > -1 && node.key === 'masculinos')
                || ($.inArray(genero.toLowerCase(), ['femininos', 'feminino', 'f', 'fem', 'mulher', 'mulheres']) > -1 && node.key === 'femininos')
            )
        ) {
            return node.value;
        }
    });

    if (nomes.isEmpty()) {
        console.log('Não há nomes com o valor informado.');
    }

    var sobrenomes = new JefNode(RF_etnias).filter(function(node) {
        if (
            $.isArray(node.value)
            && (
                !etnia
                || $.inArray(etnia, [node.parent.key, node.parent.parent.key]) > -1
            ) && node.key === 'sobrenomes'
        ) {
            return node.value;
        }
    });

    if (sobrenomes.isEmpty()) {
        console.log('Não há sobrenomes com o valor informado.');
    }

    return RPG.gerarNome(nomes, sobrenomes);
};

RPG.init();
