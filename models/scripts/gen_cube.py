size = 5

start_x = 200
start_y = 70
start_z = 25

a = {'x': start_x, 'y': start_y, 'z': start_z}
b = a.copy()
b['x'] += size
d = a.copy()
d['y'] += size
e = a.copy()
e['z'] += size
f = e.copy()
f['x'] += size
l = e.copy()
l['y'] += size
g = l.copy()
g['x'] += size
c = d.copy()
c['x'] += size

print '[[{},{},{}][{},{},{}][{},{},{}][{},{},{}]]'.format(
    a['x'], a['y'], a['z'],
    b['x'], b['y'], b['z'],
    c['x'], c['y'], c['z'],
    d['x'], d['y'], d['z']
)
print '[[{},{},{}][{},{},{}][{},{},{}][{},{},{}]]'.format(
    a['x'], a['y'], a['z'],
    e['x'], e['y'], e['z'],
    f['x'], f['y'], f['z'],
    b['x'], b['y'], b['z']
)
print '[[{},{},{}][{},{},{}][{},{},{}][{},{},{}]]'.format(
    a['x'], a['y'], a['z'],
    e['x'], e['y'], e['z'],
    l['x'], l['y'], l['z'],
    d['x'], d['y'], d['z']
)
print '[[{},{},{}][{},{},{}][{},{},{}][{},{},{}]]'.format(
    c['x'], c['y'], c['z'],
    d['x'], d['y'], d['z'],
    l['x'], l['y'], l['z'],
    g['x'], g['y'], g['z']
)
print '[[{},{},{}][{},{},{}][{},{},{}][{},{},{}]]'.format(
    c['x'], c['y'], c['z'],
    b['x'], b['y'], b['z'],
    f['x'], f['y'], f['z'],
    g['x'], g['y'], g['z']
)
print '[[{},{},{}][{},{},{}][{},{},{}][{},{},{}]]'.format(
    e['x'], e['y'], e['z'],
    f['x'], f['y'], f['z'],
    g['x'], g['y'], g['z'],
    l['x'], l['y'], l['z']
)
