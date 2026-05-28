(function () {
  'use strict';

  var overlay, img, caption;

  function build() {
    overlay = document.createElement('div');
    overlay.id = 'lb-overlay';
    overlay.setAttribute('role', 'dialog');
    overlay.setAttribute('aria-modal', 'true');
    overlay.setAttribute('aria-label', 'Image preview');

    img = document.createElement('img');
    img.id = 'lb-img';
    img.alt = '';

    caption = document.createElement('p');
    caption.id = 'lb-caption';

    var close = document.createElement('button');
    close.id = 'lb-close';
    close.setAttribute('aria-label', 'Close');
    close.innerHTML = '&#x2715;';
    close.addEventListener('click', hide);

    overlay.appendChild(close);
    overlay.appendChild(img);
    overlay.appendChild(caption);
    document.body.appendChild(overlay);

    overlay.addEventListener('click', function (e) {
      if (e.target === overlay) hide();
    });

    document.addEventListener('keydown', function (e) {
      if (e.key === 'Escape') hide();
    });
  }

  function show(src, alt, cap) {
    if (!overlay) build();
    img.style.width = '';
    img.style.height = '';
    img.onload = function () {
      img.style.width  = img.naturalWidth  * 2 + 'px';
      img.style.height = img.naturalHeight * 2 + 'px';
    };
    img.src = src;
    img.alt = alt || '';
    caption.textContent = cap || '';
    caption.style.display = cap ? '' : 'none';
    overlay.classList.add('lb-visible');
    document.body.style.overflow = 'hidden';
    overlay.focus();
  }

  function hide() {
    if (!overlay) return;
    overlay.classList.remove('lb-visible');
    document.body.style.overflow = '';
    img.src = '';
  }

  function init() {
    var figures = document.querySelectorAll('.wiki-content figure img, .wiki-content .bld-image-wrap img, .wiki-content [style] img');
    // broader: any img inside .wiki-content
    var imgs = document.querySelectorAll('.wiki-content img');
    imgs.forEach(function (el) {
      // skip tiny icons or images without a real src
      if (!el.src || el.width < 32) return;
      el.classList.add('lb-zoomable');
      el.addEventListener('click', function () {
        var fig = el.closest('figure');
        var capEl = fig && fig.querySelector('figcaption');
        show(el.src, el.alt, capEl ? capEl.textContent : '');
      });
    });
  }

  if (document.readyState === 'loading') {
    document.addEventListener('DOMContentLoaded', init);
  } else {
    init();
  }
}());
