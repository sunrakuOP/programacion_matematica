(function(){
  var KEY = 'ruta-fem-progreso';
  var TOTAL = 38;
  var BLOCKS = {
    b1: ['t01','t02','t03','t04','t05'],
    b2: ['t06','t07','t08','t09'],
    b3: ['t10','t11','t12','t13','t14'],
    b4: ['t15','t16','t17','t18','t19','t20'],
    b5: ['t21','t22','t23','t24'],
    b6: ['t25','t26','t27','t28','t29','t30','t31','t32','t33','t34'],
    b7: ['t35','t36','t37'],
    b8: ['t38']
  };

  function load(){ try{ return JSON.parse(localStorage.getItem(KEY) || '{}'); }catch(e){ return {}; } }
  function save(state){ try{ localStorage.setItem(KEY, JSON.stringify(state)); }catch(e){} }
  var state = load();

  function countDone(ids){ return ids.filter(function(id){ return !!state[id]; }).length; }

  function applyState(){
    var doneCount = 0;
    Object.keys(BLOCKS).forEach(function(b){ doneCount += countDone(BLOCKS[b]); });

    document.querySelectorAll('input[type=checkbox][data-t]').forEach(function(cb){
      var id = cb.getAttribute('data-t');
      var isDone = !!state[id];
      cb.checked = isDone;
      var el = document.getElementById(id);
      if(el) el.classList.toggle('done', isDone);
    });

    var fracEl = document.getElementById('global-frac');
    if(fracEl) fracEl.textContent = doneCount + '/' + TOTAL;

    document.querySelectorAll('[data-block-frac]').forEach(function(el){
      var b = el.getAttribute('data-block-frac');
      if(BLOCKS[b]) el.textContent = countDone(BLOCKS[b]) + '/' + BLOCKS[b].length;
    });
  }

  document.querySelectorAll('input[type=checkbox][data-t]').forEach(function(cb){
    cb.addEventListener('change', function(){
      state[cb.getAttribute('data-t')] = cb.checked;
      save(state);
      applyState();
    });
  });

  applyState();
})();
