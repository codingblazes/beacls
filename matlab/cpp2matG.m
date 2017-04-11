function g = cpp2matG(gCPP)
    g = gCPP;
    g.bdryData = cell(g.dim, 1);
    g.bdry = cell(g.dim, 1);
    g.min = double(g.min);
    g.max = double(g.max);
    g.dx = double(g.dx);
    for i=1:length(g.vs)
        g.vs{i} = double(g.vs{i});
    end
    g.axis = double(g.axis);
    for i=1:length(g.bdry_type)
        switch(g.bdry_type(i))
        case 0
        case 1
            g.bdry{i} = @addGhostPeriodic;
        case 2   
            g.bdry{i} = @addGhostExtrapolate;
        otherwise
            error('Unknown Boundary Type!')
        end
    end
    g.shape = double(g.shape');
    g = processGrid(g);
end